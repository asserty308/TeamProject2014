#pragma once

#include "AudioFiles.hpp"
#include "AudioController.hpp"
#include "NetRocket.h"
#include "Game.hpp"
#include "ParticleSystem.hpp"

NetRocket::NetRocket() : TransformCollidable(Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f)){
	// TODO: delete?
}

NetRocket::NetRocket(Netplayer* owner, Vector2 position, Vector2 forward) : TransformCollidable(position, forward, Vector2(1.0f, 1.0f)){
	g_pCollisionObserver->addListener(this);

	boundingBox = new CircleBoundingBox(position, 10.0f);

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

	firstImpact = false;

	this->owner = owner;
}

NetRocket::~NetRocket(){
	delete sprite;
	delete boundingBox;

	g_pAudioController->stopSoundByFile(SoundFiles::EXPLOSION);
}

void NetRocket::CollisionDetected(TransformCollidable *other, Vector2 penetration){
	if (other == owner){
		return;
	}

	if (!firstImpact){
		sprite->playAnimation(0, 0.05f, false);
		firstImpact = true;
		g_pAudioController->playSound(SoundFiles::EXPLOSION, false);
	}

}

void NetRocket::update(Vector2 position, Vector2 forward){
	setForward(forward);

	this->position = position;
	boundingBox->setPosition(position + forward * 10.0f);

	sprite->setPosition(position);
	sprite->setAngle(angleFromVector<float>(forward));

	Vector2 exhaustVector = forward * -1.f;
	exhaustVector.setX(exhaustVector.getX() + ((rand() % 100) / 100.f - .5f) * .6f);
	exhaustVector.setY(exhaustVector.getY() + ((rand() % 100) / 100.f - .5f) * .6f);
	g_pParticleSystem->spawnParticle(ParticleType::Smoke, position, exhaustVector, 55);

	if (firstImpact && !sprite->isPlayingAnimation())
	{
		// spawn four diagonal explosions
		g_pParticleSystem->spawnParticle(ParticleType::Explosion, position, Vector2(-.3f, -.3f), 50);
		g_pParticleSystem->spawnParticle(ParticleType::Explosion, position, Vector2(-.3f, .3f), 50);
		g_pParticleSystem->spawnParticle(ParticleType::Explosion, position, Vector2(.3f, -.3f), 50);
		g_pParticleSystem->spawnParticle(ParticleType::Explosion, position, Vector2(.3f, .3f), 50);

		firstImpact = false;

		owner->rocketDestroyed();
	}
}

void NetRocket::playAnimation(int index, float speed, bool loop){
	if (!sprite->isPlayingAnimation()){
 		sprite->playAnimation(index, 0.2f, loop);
	}
}


	