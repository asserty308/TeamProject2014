#pragma once

#include "TransformCollidable.h"
#include "InputObserver.h"
#include "Timer.h"
#include "Player.hpp"

#include <SDL_opengl.h>

class Player;

class Rocket : public TransformCollidable, public Inputlistener
{
	private:
		static const float SPEED;
		//static const float TURN_ACCELERATION;
		//static const float TURN_SPEED;

		bool controllable;
		bool isLeftKeyDown, isRightKeyDown;

		Player *owner;

	public:
		Rocket(Player* owner, Vector2 position, Vector2 forward);
		~Rocket();

		virtual void inputReceived(SDL_KeyboardEvent *key);
		virtual void CollisionDetected(TransformCollidable *other, Vector2 penetration);

		bool getControllable();

		void update();
		void render();
};

