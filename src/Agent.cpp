#include "Agent.hpp"
#include "Util.hpp"
#include "Slime.hpp"

Agent::Agent() : 
    rbg(rand01(), rand01(), rand01()) 
{
    x = rand01() * GRID_WIDTH;
    y = rand01() * GRID_HEIGHT;

    heading = rand01() * 2 * M_PI;
}

Agent::Agent(float r, float b, float g) : 
    rbg(rand01() * r, rand01() * b, rand01() * g) 
{

    x = rand01() * GRID_WIDTH;
    y = rand01() * GRID_HEIGHT;

    heading = rand01() * 2 * M_PI;
}

void Agent::jitter(float force) {
    x = modIndex(x + ((0.5f - rand01()) * force), GRID_WIDTH);
    y = modIndex(y + ((0.5f - rand01()) * force), GRID_HEIGHT);
}

Agent::~Agent() {}