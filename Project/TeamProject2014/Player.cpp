#include <SDL_opengl.h>
#include "Logger.hpp"
#include "InputObserver.h"
#include "Player.hpp"

const float Player::ACCELERATION = .38f;
const float Player::TURN_SPEED = 5.f;

Player::Player(Vector2 position, Vector2 forward) : Transform(position, forward, Vector2(0.0f, 0.0f))
{
	isThrustKeyDown = isLeftKeyDown = isRightKeyDown = false;
	g_pInputObserver->addListener(this);
}

void Player::inputReceived(SDL_KeyboardEvent *key)
{
	if (key->keysym.sym == SDLK_w)
		isThrustKeyDown = (key->type == SDL_KEYDOWN);
	else if (key->keysym.sym == SDLK_a)
		isLeftKeyDown = (key->type == SDL_KEYDOWN);
	else if (key->keysym.sym == SDLK_d)
		isRightKeyDown = (key->type == SDL_KEYDOWN);
}

void Player::update()
{
	if (isThrustKeyDown)
		setAcceleration(forward * ACCELERATION);
	else
		setAcceleration(Vector2(0.0f, 0.0f));

	if (isLeftKeyDown && !isRightKeyDown)
		rotate(TURN_SPEED);
	else if (isRightKeyDown && !isLeftKeyDown)
		rotate(-TURN_SPEED);

	if (getPosition().getX() < 0.f)
	{
		position.setX(0.f);
		velocity.setX(-velocity.getX() * .25f);
	}
	else if (getPosition().getX() > 4.f)
	{
		position.setX(4.f);
		velocity.setX(-velocity.getX() * .25f);
	}

	if (getPosition().getY() < 0.f)
	{
		position.setY(0.f);
		velocity.setY(-velocity.getY() *.25f);
	}
	else if (getPosition().getY() > 3.f)
	{
		position.setY(3.f);
		velocity.setY(-velocity.getY() *.25f);
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