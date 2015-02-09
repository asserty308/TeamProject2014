#pragma once

#include "Rocket.hpp"
#include "Sprite.hpp"
#include "TransformCollidable.h"

class Rocket;

class Player : public TransformCollidable, public Inputlistener
{
	private:
		static const float TOP_SPEED;
		static const float ACCELERATION;
		static const float TURN_SPEED;

		bool isThrustKeyDown, isLeftKeyDown, isRightKeyDown, isFirePressed;
		bool isDead;

		float accelFactor;

		void die();

		Rocket *rocket;
		Sprite *sprite;

	public:
		Player(Vector2 position, Vector2 forward);
		virtual ~Player();

		virtual void inputReceived(SDL_KeyboardEvent *key);
		virtual void CollisionDetected(TransformCollidable *other, Vector2 penetration);

		void update();
		//void render();

		void handleRocket();
		void rocketDestroyed();
		bool rocketAlive();

		bool getIsDead();

		void reset();

		Rocket* getRocket();

		Sprite* getSprite();

		
};