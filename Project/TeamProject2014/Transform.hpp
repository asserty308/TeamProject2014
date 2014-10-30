#pragma once

#include "Vector2.hpp"

class Transform
{
	protected:
		Vector2 position;
		Vector2 forward;
		Vector2 acceleration;
		Vector2 velocity;

	public:
		Transform(Vector2 position, Vector2 forward, Vector2 velocity);

		Vector2 getPosition() const;
		void setPosition(Vector2 position);
		Vector2 getForward() const;
		void setForward(Vector2 forward);
		Vector2 getRight() const;
		Vector2 getVelocity() const;
		void setVelocity(Vector2 velocity);
		Vector2 getAcceleration() const;
		void setAcceleration(Vector2 velocity);

		void rotate(float angle);

		virtual void updatePosition(float deltaTime);
};