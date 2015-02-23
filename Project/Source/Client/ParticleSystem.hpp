#pragma once

#include <vector>

#include "Particle.hpp"
#include "Singleton.hpp"
#include "Sprite.hpp"

#define g_pParticleSystem ParticleSystem::Get()

class ParticleSystem : public Singleton<ParticleSystem>
{
private:
	std::vector<Particle*> particles;
	Sprite *smokeSprite, *explosionSprite;

public:
	ParticleSystem();

	void spawnParticle(ParticleType type, Vector2 position, Vector2 velocity, int timeToLive);
	void update();
	void render();
};