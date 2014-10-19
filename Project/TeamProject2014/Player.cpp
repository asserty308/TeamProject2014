#include <SDL_opengl.h>
#include "Logger.hpp"
#include "InputObserver.h"
#include "Player.hpp"

Player::Player(Vector2 position, Vector2 forward) : Transform(position, forward, Vector2(0.0f, 0.0f))
{
	accelerating = false;
	accelFactor = 0.25f;
	g_pInputObserver->addListener(this);
}

void Player::inputReceived(SDL_KeyboardEvent *key)
{
	if (key->keysym.sym == SDLK_w)
	{
		setAcceleration(forward * accelFactor);
		if(key->type == SDL_KEYDOWN){
			accelerating = true;
		}else if(key->type == SDL_KEYUP){
			accelerating = false;
		}
	}
	else if (key->keysym.sym == SDLK_a)
	{
		rotate(5.f);
	}
	else if (key->keysym.sym == SDLK_d)
	{
		rotate(-5.f);
	}
}

void Player::update(){
	if(!accelerating){
		setAcceleration(Vector2(0.0f, 0.0f));
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