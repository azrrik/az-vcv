#pragma once

class RBG {
public:
	float r,b,g;

	RBG(): r(0.), b(0.), g(0.)
	{}

	RBG(float r, float b, float g): 
		r(r), b(b), g(g)
	{}

	inline float avg() {
		return (r + b + g) / 3.;
	}

	inline void zero() {
		r = 0.;
		g = 0.;
		b = 0.;
	}
};

class Agent {
public:
	float x, y;
	float heading;
	RBG rbg;
    Agent();
	~Agent();
    Agent(float r, float b, float g);
	void jitter(float force);
};