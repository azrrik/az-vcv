#pragma once
#include "widget/Widget.hpp"
#include "Agent.hpp"

#define GRID_WIDTH 127
#define GRID_HEIGHT 127

#define AGENT_WIDTH 3
#define AGENT_HEIGHT 3

using namespace std;
struct Modulation {
	float mod3;
	float mod5;
	float mod7;

	Modulation(float mod3, float mod5, float mod7) : 
		mod3(mod3), mod5(mod5), mod7(mod7) 
	{};
};

class Slime {
private:
	Slime();
	vector<unique_ptr<Agent>> agents;
	vector<vector<RBG>> trailMap;
	vector<vector<RBG>> trailMapTemp;
	float getDecimalPart(float number);
public:
	Slime(int totalAgents, float redWeight, float blueWeight, float greenWeight);
	~Slime();
	void reset(int totalAgents, float redWeight, float blueWeight, float greenWeight);
	void renderAgents(const rack::widget::Widget::DrawArgs& args);
	void renderTrailMap(const rack::widget::Widget::DrawArgs& args, rack::math::Rect& box);
	void dumpTrailMap();
	void step(float sensorAngle, int sensorOffset, 	float diffusionFactor, float retainmentFactor);
	void jitter(float force);
	Modulation getModulation();
};
