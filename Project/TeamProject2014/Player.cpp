#include <SDL_opengl.h>

#include "Player.hpp"

Player::Player(Vector2 position, Vector2 forward)
{
	this->position = position;
	this->forward = forward;
}

void Player::render()
{
	glColor3f(0.f, 1.f, 0.f);
	glRectf(getPosition().getX() - 0.1f, getPosition().getY() - 0.1f, getPosition().getX() + 0.1f, getPosition().getY() + 0.1f);
}