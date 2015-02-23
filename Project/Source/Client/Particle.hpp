#pragma once

#include "Vector2.hpp"

enum ParticleType
{
	Smoke,
	Explosion
};

class Particle
{
private:
	ParticleType type;
	Vector2 position;
	Vector2 velocity;
	int timeToLive;
	int maxTime;
	int frame;

public:
	Particle(ParticleType type, Vector2 position, Vector2 velocity, int timeToLive);

	ParticleType getType();
	Vector2 getPosition();
	bool getDead();
	int getFrame();
	void update();
};