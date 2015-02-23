#include "ParticleSystem.hpp"

ParticleSystem::ParticleSystem()
{
	//create sprites

	smokeSprite = new Sprite("Sprites\\smoke_sheet.png", Vector2(0.f, 0.f), Vector2(6.f, 5.f), 3);
	std::vector<int> smokeAnimation;
	smokeAnimation.push_back(0);
	smokeAnimation.push_back(1);
	smokeAnimation.push_back(2);
	smokeSprite->addAnimation(smokeAnimation);

	explosionSprite = new Sprite("Sprites\\explosion_sheet.png", Vector2(0.f, 0.f), Vector2(24.f, 24.f), 9);
	std::vector<int> explosionAnimation;
	explosionAnimation.push_back(0);
	explosionAnimation.push_back(1);
	explosionAnimation.push_back(2);
	explosionAnimation.push_back(3);
	explosionAnimation.push_back(4);
	explosionAnimation.push_back(5);
	explosionAnimation.push_back(6);
	explosionAnimation.push_back(7);
	explosionAnimation.push_back(8);
	explosionSprite->addAnimation(explosionAnimation);
}

void ParticleSystem::spawnParticle(ParticleType type, Vector2 position, Vector2 velocity, int timeToLive)
{
	particles.push_back(new Particle(type, position, velocity, timeToLive));
}

void ParticleSystem::update()
{
	auto i = std::begin(particles);

	while (i != std::end(particles))
	{
		(*i)->update();

		// do some stuff
		if ((*i)->getDead())
			i = particles.erase(i);
		else
			++i;
	}
}

void ParticleSystem::render()
{
	for (Particle *i : particles)
	{
		if (i->getType() == ParticleType::Smoke)
		{
			smokeSprite->setPosition(i->getPosition());
			smokeSprite->render(i->getFrame());
		}
		else if (i->getType() == ParticleType::Explosion)
		{
			explosionSprite->setPosition(i->getPosition());
			explosionSprite->render(i->getFrame());
		}
	}
}