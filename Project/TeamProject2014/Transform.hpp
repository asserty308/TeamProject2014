#pragma once

#include "Vector2.hpp"

class Transform
{
	protected:
		Vector2 position;
		Vector2 forward;
		Vector2 boost;
		float velocity;

	public:
		Transform(Vector2 position, Vector2 forward, float velocity);
		Transform(Vector2 position, Vector2 forward);
		Transform();

		Vector2 getPosition() const;
		void setPosition(Vector2 position);
		Vector2 getForward() const;
		void setForward(Vector2 forward);
		float getVelocity() const;
		void setVelocity(float velocity);

		void rotate(float angle);

		void updatePosition(float deltaTime);
};