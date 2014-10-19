#include <SDL_opengl.h>
#include "Logger.hpp"
#include "InputObserver.h"
#include "Player.hpp"

Player::Player(Vector2 position, Vector2 forward)
{
	this->position = position;
	this->forward = forward;
	this->boost = forward;
	this->velocity = 0.f;

	g_pInputObserver->addListener(this);
}

void Player::inputReceived(SDL_KeyboardEvent *key)
{
	if (key->keysym.sym == SDLK_w)
	{
		this->boost = this->forward; //boosting will update the boost vector
		setVelocity(getVelocity() + .025f);

		if (getVelocity() > 1.f)
			setVelocity(1.f);
	}
	else if (key->keysym.sym == SDLK_a)
	{
		rotate(5.f);
		setVelocity(getVelocity() - .01f);

		if (getVelocity() <= 0.f)
			setVelocity(0.f);
	}
	else if (key->keysym.sym == SDLK_d)
	{
		rotate(-5.f);
		setVelocity(getVelocity() - .01f);

		if (getVelocity() <= 0.f)
			setVelocity(0.f);
	}
}

void Player::render()
{
	glColor3f(0.f, 1.f, 0.f);
	
	glLineWidth(2.f);

	glBegin(GL_LINES);

	for (int i = 0; i < 36; ++i)
	{
		float angle = (i * M_PI / 180.0) * 10.0;
		glVertex2f(getPosition().getX() + sin(angle) * .05f, getPosition().getY() + cos(angle) * .05f);
		angle = ((i + 1) * M_PI / 180.0) * 10.0;
		glVertex2f(getPosition().getX() + sin(angle) * .05f, getPosition().getY() + cos(angle) * .05f);
	}

	glVertex2f(getPosition().getX() + getForward().getX() * .025f, getPosition().getY() + getForward().getY() * .025f);
	glVertex2f(getPosition().getX() + getForward().getX() * .075f, getPosition().getY() + getForward().getY() * .075f);

	glEnd();
}