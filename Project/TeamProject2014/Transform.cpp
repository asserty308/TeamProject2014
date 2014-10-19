#define _USE_MATH_DEFINES
#include <cmath>

#include "Transform.hpp"

Transform::Transform(Vector2 position, Vector2 forward, float velocity)
{
	this->position = position;
	this->forward = forward;
	this->velocity = velocity;
}

Transform::Transform(Vector2 position, Vector2 forward)
{
	Transform(position, forward, 0.f);
}

Transform::Transform()
{
	Transform(Vector2(0.f, 0.f), Vector2(1.f, 0.f));
}

Vector2 Transform::getPosition() const
{
	return position;
}

void Transform::setPosition(Vector2 position)
{
	this->position = position;
}

Vector2 Transform::getForward() const
{
	return forward;
}

void Transform::setForward(Vector2 forward)
{
	this->forward = forward;
}

float Transform::getVelocity() const
{
	return velocity;
}

void Transform::setVelocity(float velocity)
{
	this->velocity = velocity;
}

void Transform::rotate(float angle)
{
	float theta = angle * M_PI / 180.0;

	float c = cos(theta);
	float s = sin(theta);

	forward.setX(forward.getX() * c - forward.getY() * s);
	forward.setY(forward.getX() * s + forward.getY() * c);

	forward.normalize();
}

void Transform::updatePosition(float deltaTime)
{
	position += forward * velocity * deltaTime;
}