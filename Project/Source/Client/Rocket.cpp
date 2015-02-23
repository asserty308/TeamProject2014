#include "Logger.hpp"
#include "Rocket.hpp"
#include "AudioController.hpp"
#include "CollisionObserver.h"
#include "AudioFiles.hpp"
#include "MathUtil.h"
#include "ParticleSystem.hpp"
#include <math.h>

const float Rocket::TURN_SPEED = 5.f;
const float Rocket::TURN_ACCELERATION = 50.f;
const float Rocket::MAX_TORQUE = 4.f;

Rocket::Rocket(Player* owner, Vector2 position, Vector2 forward) : TransformCollidable(position, forward, Vector2(0.f, 0.f))
{
	g_pInputObserver->addListener(this);
	g_pCollisionObserver->addListener(this);

	boundingBox = new CircleBoundingBox(position, 10.0f);

	controllable = true;
	isLeftKeyDown = isRightKeyDown = false;
	firstImpact = false;

	speed = 400.0f;
	torque = 0.0f;
	torqueDir = 0.0f;

	this->owner = owner;

	//create sprite
	sprite = new Sprite("Sprites\\new_rocket_sheet.png", position, Vector2(14.f, 24.f), 8);
	std::vector<int> explosionAnimation;
	explosionAnimation.push_back(0);
	explosionAnimation.push_back(1);
	explosionAnimation.push_back(2);
	explosionAnimation.push_back(3);
	sprite->addAnimation(explosionAnimation);

	std::vector<int> travelAnimation;
	travelAnimation.push_back(4);
	travelAnimation.push_back(5);
	travelAnimation.push_back(6);
	travelAnimation.push_back(7);
	sprite->addAnimation(travelAnimation);

	sprite->playAnimation(1, 0.2f, false); //play travel animation on instancing


	g_pAudioController->playSound(SoundFiles::ROCKET, false);
}

Rocket::~Rocket()
{
	delete sprite;
	delete boundingBox;

	g_pInputObserver->removeListener(this);
	g_pCollisionObserver->removeListener(this);

	g_pAudioController->stopSoundByFile(SoundFiles::EXPLOSION);
	g_pAudioController->stopSoundByFile(SoundFiles::ROCKET);
}

void Rocket::inputReceived(SDL_KeyboardEvent *key)
{
	if (!controllable)
		return;

	if (key->type == SDL_KEYDOWN)
	{
		if (key->keysym.sym == SDLK_a && !isLeftKeyDown)
		{
			torqueDir = -1.0f;
			isLeftKeyDown = true;
		}
		else if (key->keysym.sym == SDLK_d && !isRightKeyDown)
		{
			torqueDir = 1.0f;
			isRightKeyDown = true;
		}

	}
	else if (key->type == SDL_KEYUP)
	{
		if (key->keysym.sym == SDLK_SPACE)
			controllable = false;
		else if (key->keysym.sym == SDLK_a){
			isLeftKeyDown = false;
			torque = 0.0f;

			if (isRightKeyDown){
				torqueDir = 1.0f;
			}
		} else if (key->keysym.sym == SDLK_d){
			isRightKeyDown = false;
			torque = 0.0f;


			if (isLeftKeyDown){
				torqueDir = -1.0f;
			}
		}
	}
}

void Rocket::CollisionDetected(TransformCollidable *other, Vector2 penetration){
	if (other == owner){
		return;
	}

	this->velocity = Vector2(0.0f, 0.0f);
	this->acceleration = Vector2(0.0f, 0.0f);

	if (!firstImpact){
		sprite->playAnimation(0, 0.05f, false);
		firstImpact = true;
		g_pAudioController->playSound(SoundFiles::EXPLOSION, false);
	}

	speed = 0.0f;
}

bool Rocket::getControllable()
{
	return controllable;
}

void Rocket::update()
{
	// make sure the velocity of the rocket is constant
	// and always towards the current forward vector
	if (isLeftKeyDown || isRightKeyDown){
		if (std::abs(torque) < MAX_TORQUE){
			torque += torqueDir * TURN_SPEED * g_pTimer->getDeltaTime();
		}
	} else{
		torque = 0.0f;
	}

	if (!firstImpact)
	// don't rotate the rocket when it's already exploding
	{
		rotate(torque);

		Vector2 exhaustVector = forward * -1.f;
		exhaustVector.setX(exhaustVector.getX() + ((rand() % 100) / 100.f - .5f) * .6f);
		exhaustVector.setY(exhaustVector.getY() + ((rand() % 100) / 100.f - .5f) * .6f);
		g_pParticleSystem->spawnParticle(ParticleType::Smoke, position, exhaustVector, 55);
	}

	setVelocity(forward * speed);

	updatePosition(g_pTimer->getDeltaTime());
	sprite->setPosition(position);
	sprite->setAngle(angleFromVector<float>(forward));

	if (firstImpact && !sprite->isPlayingAnimation())
	{
		// spawn four diagonal explosions
		g_pParticleSystem->spawnParticle(ParticleType::Explosion, position, Vector2(-.3f, -.3f), 50);
		g_pParticleSystem->spawnParticle(ParticleType::Explosion, position, Vector2(-.3f, .3f), 50);
		g_pParticleSystem->spawnParticle(ParticleType::Explosion, position, Vector2(.3f, -.3f), 50);
		g_pParticleSystem->spawnParticle(ParticleType::Explosion, position, Vector2(.3f, .3f), 50);

		owner->rocketDestroyed();
	}

}
