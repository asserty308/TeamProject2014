#pragma once

#include "Transform.hpp"

class Player : public Transform
{
	private:

	public:
		Player(Vector2 position, Vector2 forward);

		void render();
};