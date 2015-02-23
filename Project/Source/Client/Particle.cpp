#include "Particle.hpp"

Particle::Particle(ParticleType type, Vector2 position, Vector2 velocity, int timeToLive)
{
	this->type = type;
	this->position = position;
	this->velocity = velocity;
	this->timeToLive = timeToLive;
	
	maxTime = timeToLive;
	frame = 0;
}

ParticleType Particle::getType()
{
	return type;
}

Vector2 Particle::getPosition()
{
	return position;
}

bool Particle::getDead()
{
	return timeToLive <= 0;
}

int Particle::getFrame()
{
	return frame;
}

void Particle::update()
{
	position += velocity;
	timeToLive--;

	if (type == ParticleType::Smoke)
	{
		if (timeToLive < (1.f / 3.f) * maxTime)
			frame = 2;
		else if (timeToLive < (2.f / 3.f) * maxTime)
			frame = 1;
		else
			frame = 0;
	}
	else if (type == ParticleType::Explosion)
	{
		if (timeToLive < (1.f / 9.f) * maxTime)
			frame = 8;
		else if (timeToLive < (2.f / 9.f) * maxTime)
			frame = 7;
		else if (timeToLive < (3.f / 9.f) * maxTime)
			frame = 6;
		else if (timeToLive < (4.f / 9.f) * maxTime)
			frame = 5;
		else if (timeToLive < (5.f / 9.f) * maxTime)
			frame = 4;
		else if (timeToLive < (6.f / 9.f) * maxTime)
			frame = 3;
		else if (timeToLive < (7.f / 9.f) * maxTime)
			frame = 2;
		else if (timeToLive < (8.f / 9.f) * maxTime)
			frame = 1;
		else
			frame = 0;
	}
}