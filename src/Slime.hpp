#pragma once
#include "widget/Widget.hpp"
#include "Agent.hpp"

#define GRID_WIDTH 110
#define GRID_HEIGHT 110

#define AGENT_WIDTH 3
#define AGENT_HEIGHT 3

class Slime {
public:
	Slime(int totalAgents, float redWeight, float blueWeight, float greenWeight);
	~Slime();
	void reset(int totalAgents, float redWeight, float blueWeight, float greenWeight);
	RBG getKernel(int x, int y, int size);
	void diffuse(int x, int y, int size);
	void renderAgents(const rack::widget::Widget::DrawArgs& args);
	void renderTrailMap(const rack::widget::Widget::DrawArgs& args, rack::math::Rect& box);
	void dumpTrailMap();
	void step(float sensorAngle, int sensorOffset, 	float diffusionFactor, float retainmentFactor);
	void jitter(float force);
};
