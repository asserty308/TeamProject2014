#pragma once

#include "TransformCollidable.h"
#include "InputObserver.h"
#include "Sprite.hpp"
#include "Timer.h"
#include "Player.hpp"
#include "Netplayer.h"

#include <SDL_opengl.h>

class Player;

class Rocket : public TransformCollidable, public Inputlistener
{
	private:
		static const float TURN_ACCELERATION;
		static const float TURN_SPEED;
		static const float MAX_TORQUE;

		float speed;
		float torque;
		float torqueDir;

		bool controllable;
		bool isLeftKeyDown, isRightKeyDown;
		bool firstImpact;

		Player *owner;

		Sprite *sprite;

	public:
		Rocket(Player* owner, Vector2 position, Vector2 forward);
		~Rocket();

		virtual void inputReceived(SDL_KeyboardEvent *key);
		virtual void CollisionDetected(TransformCollidable *other, Vector2 penetration);

		bool getControllable();
		
		void update();
		//void render();
};

