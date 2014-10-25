#pragma once

#include "Rocket.hpp"
#include "Sprite.hpp"

class Player : public Transform, public Inputlistener
{
	private:
		static const float ACCELERATION;
		static const float TURN_SPEED;

		bool isThrustKeyDown, isLeftKeyDown, isRightKeyDown;
		bool isRocketLaunched, renderRocket; //rocket-specific
		float accelFactor;

		Rocket *rocket;
		Sprite *sprite;

	public:
		Player(Vector2 position, Vector2 forward);

		virtual void inputReceived(SDL_KeyboardEvent *key);

		void update();
		void render();

		void handleRocket();
};