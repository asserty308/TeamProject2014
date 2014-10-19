#define _USE_MATH_DEFINES
#include <cmath>

#include "Transform.hpp"

Transform::Transform(Vector2 position, Vector2 forward, Vector2 velocity)
{
	this->position = position;
	this->forward = forward;
	this->velocity = velocity;
	this->acceleration = Vector2(0.0f, 0.0f);
}

//It is not possible to call constructors from within other constructors in C++, 
//at least not in the Java sense :S
/*
Transform::Transform(Vector2 position, Vector2 forward)
{
	Transform(position, forward, Vector2(0.0f, 0.0f));
}

Transform::Transform()
{
	Transform(Vector2(0.f, 0.f), Vector2(1.f, 0.f));
}
*/

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

Vector2 Transform::getVelocity() const
{
	return velocity;
}

void Transform::setVelocity(Vector2 velocity)
{
	this->velocity = velocity;
}

Vector2 Transform::getAcceleration() const{
	return acceleration;
}

void Transform::setAcceleration(Vector2 acceleration){
	this->acceleration = acceleration;
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
	//Textbook Euler 
	position += velocity * deltaTime;
	velocity += acceleration * deltaTime;
}