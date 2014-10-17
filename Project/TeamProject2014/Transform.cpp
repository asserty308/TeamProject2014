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

void Transform::updatePosition()
{
	position += forward * velocity;
}