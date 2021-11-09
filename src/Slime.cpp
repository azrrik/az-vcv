#include "Slime.hpp"
#include "Util.hpp"

#include <memory>
#include <vector>
#include <cstdint>

using namespace std;

Slime::Slime(int totalAgents, float redWeight, float blueWeight, float greenWeight) {
	for (int i = 0; i < totalAgents; i++) {
		agents.push_back(unique_ptr<Agent>(new Agent(redWeight, blueWeight, greenWeight)));
	}

	for (int i = 0; i < GRID_WIDTH; i++) {
		vector<RBG> temp;
		vector<RBG> temp2;
		for (int j = 0; j < GRID_HEIGHT; j++) {
			RBG rbg;
			temp.push_back(rbg);
			RBG rbg2;
			temp2.push_back(rbg2);
		}
		trailMap.push_back(temp);
		trailMapTemp.push_back(temp);
	}
}

Slime::~Slime() {
	agents.clear();
}

void Slime::reset(int totalAgents, float redWeight, float blueWeight, float greenWeight) {
	agents.clear();

	for (int i = 0; i < totalAgents; i++) {
		agents.push_back(unique_ptr<Agent>(new Agent(redWeight, blueWeight, greenWeight)));
	}

	// trialMap and trailMapTemp have the same dimensions
	for (size_t i = 0; i < trailMap.size(); ++i) {
		for(size_t j = 0; j < trailMap[i].size(); ++j) {
			trailMap[i][j].zero();
			trailMapTemp[i][j].zero();
		}
	}
}

void Slime::renderAgents(const rack::widget::Widget::DrawArgs& args) {
	for (auto&& agent : agents) {
		nvgBeginPath(args.vg);
		nvgRoundedRect(
			args.vg, 
			agent->x * AGENT_WIDTH, 
			agent->y * AGENT_HEIGHT, 
			AGENT_WIDTH, 
			AGENT_HEIGHT, 
			5.f
		);
		nvgFillColor(args.vg, nvgRGBA(222,30,34,192));
		nvgFill(args.vg);
	}
}


void Slime::renderTrailMap(const rack::widget::Widget::DrawArgs& args, rack::math::Rect& box) {
	nvgSave(args.vg);
	for (int j = 0; j < GRID_HEIGHT; j++) {
		for (int i = 0; i < GRID_WIDTH; i++) {
			nvgBeginPath(args.vg);
			nvgRect(
				args.vg, 
				box.pos.x + (i*AGENT_WIDTH), 
				box.pos.y + (j*AGENT_HEIGHT), 
				AGENT_WIDTH,
				AGENT_HEIGHT
			);
			RBG heat = trailMap[i][j];
			nvgFillColor(args.vg, nvgRGB(256. * heat.r, 256. * heat.g, 256. * heat.b));
			nvgFill(args.vg);				
		}
	}
	nvgRestore(args.vg);
}


void Slime::step(float sensorAngle, int sensorOffset, float diffusionFactor, float retainmentFactor) {
	random_shuffle(agents.begin(), agents.end());
	// move forward
	for (auto&& agent : agents) {
		agent->x = modIndex(agent->x + cos(agent->heading), GRID_WIDTH);
		agent->y = modIndex(agent->y + sin(agent->heading), GRID_HEIGHT);

		int nextX = modIndex(toInt(agent->x), GRID_WIDTH);
		int nextY = modIndex(toInt(agent->y), GRID_HEIGHT);

		trailMap[nextX][nextY].r += agent->rbg.r;
		trailMap[nextX][nextY].b += agent->rbg.b;
		trailMap[nextX][nextY].g += agent->rbg.g;
	}

	// sense
	for (auto&& agent : agents) {
		// front
		int frontX = modIndex(agent->x + (sensorOffset * cos(agent->heading)), GRID_WIDTH);
		int frontY = modIndex(agent->y + (sensorOffset * sin(agent->heading)), GRID_HEIGHT);
		// +sensorAngle
		int anglePlusX = modIndex(agent->x + (sensorOffset * cos(agent->heading + sensorAngle)), GRID_WIDTH);
		int anglePlusY = modIndex(agent->y + (sensorOffset * sin(agent->heading + sensorAngle)), GRID_HEIGHT);		
		// -sensorAngle
		int angleMinusX = modIndex(agent->x + (sensorOffset * cos(agent->heading - sensorAngle)), GRID_WIDTH);
		int angleMinusY = modIndex(agent->y + (sensorOffset * sin(agent->heading - sensorAngle)), GRID_HEIGHT);

		float front = trailMap[frontX][frontY].avg();
		float frontPlus = trailMap[anglePlusX][anglePlusY].avg();
		float frontMinus = trailMap[angleMinusX][angleMinusY].avg();

		if (front > frontPlus && front > frontMinus) {
			// stay on target
		} else if(front < frontPlus && front < frontMinus) {
			// coin flip
			if (rand01() > 0.5f) {
				agent->heading += sensorAngle;
			} else {
				agent->heading -= sensorAngle;
			}
		} else if(frontPlus > frontMinus) {
			agent->heading += sensorAngle;
		} else if(frontMinus > frontPlus) {
			agent->heading -= sensorAngle;
		}
	}
	// TODO : param?
	int length = 1;
	int totalArea = ((2 * length) + 1) * ((2 * length) + 1);
	for (int x = 0; x < GRID_WIDTH; x++) {
		for (int y = 0; y < GRID_HEIGHT; y++) {
			for (int i = x - length; i <= x + length; ++i) {
				for (int j = y - length; j <= y + length; ++j) {
					trailMapTemp[modIndex(i, GRID_WIDTH)][modIndex(j, GRID_HEIGHT)].r += trailMap[x][y].r / totalArea * diffusionFactor;
					trailMapTemp[modIndex(i, GRID_WIDTH)][modIndex(j, GRID_HEIGHT)].b += trailMap[x][y].b / totalArea * diffusionFactor;
					trailMapTemp[modIndex(i, GRID_WIDTH)][modIndex(j, GRID_HEIGHT)].g += trailMap[x][y].g / totalArea * diffusionFactor;
				}
			}
			trailMapTemp[x][y].r = (trailMapTemp[x][y].r + trailMap[x][y].r) * retainmentFactor;
			trailMapTemp[x][y].b = (trailMapTemp[x][y].b + trailMap[x][y].b) * retainmentFactor;
			trailMapTemp[x][y].g = (trailMapTemp[x][y].g + trailMap[x][y].g) * retainmentFactor;
		}
	}
	std::swap(trailMap, trailMapTemp);

	for (int i = 0; i < GRID_WIDTH; i++) {
		for (int j = 0; j < GRID_HEIGHT; j++) {
			trailMapTemp[i][j].zero();
		}
	}
}

void Slime::jitter(float force) {
	for (auto&& agent : agents) {
		agent->jitter(force);
	}
}

float Slime::getDecimalPart(float number) {
	double nonDecimal;
    return std::modf(number, &nonDecimal);
}

Modulation Slime::getModulation() {
	float mod3 = 0.f;
	float mod5 = 0.f;
	float mod7 = 0.f;

	for (int x = 0; x < GRID_WIDTH; ++x) {
		for (int y = 0; y < GRID_HEIGHT; ++y) {
			RBG rbg = trailMap[x][y];
			if (x % 3 == 0 || y % 3 == 0) {
				mod3 += rbg.avg();
			} else if (x % 5 == 0 || y % 5 == 0) {
				mod5 += rbg.avg();
			} else if (x % 7 == 0 || y % 7 == 0) {
				mod7 += rbg.avg();
			}
		}
	}

	// drop digits before the decimal and scale to [0,10]
	mod3 = getDecimalPart(mod3) * 10.f;
	mod5 = getDecimalPart(mod5) * 10.f;
	mod7 = getDecimalPart(mod7) * 10.f;

	return Modulation(mod3, mod5, mod7);
}