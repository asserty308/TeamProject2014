#pragma once

#include "Transform.hpp"
#include "InputObserver.h"
#include "Timer.h"

#include <SDL_opengl.h>

class Rocket : public Transform, public Inputlistener
{
	private:
		static const float SPEED;
		//static const float TURN_ACCELERATION;
		//static const float TURN_SPEED;

		bool controllable;
		bool isLeftKeyDown, isRightKeyDown;

	public:
		Rocket(Vector2 position, Vector2 forward);
		~Rocket();

		virtual void inputReceived(SDL_KeyboardEvent *key);

		bool getControllable();

		void update();
		void render();
};

