#include <SDL_opengl.h>
#include "Logger.hpp"
#include "InputObserver.h"
#include "Player.hpp"

Player::Player(Vector2 position, Vector2 forward)
{
	this->position = position;
	this->forward = forward;

	g_pInputObserver->addListener(this);
}

void Player::inputReceived(SDL_KeyboardEvent *key){
	//g_pLogfile->log("A key was pressed!"); //For demonstration purposes
}

void Player::render()
{
	glColor3f(0.f, 1.f, 0.f);
	glRectf(getPosition().getX() - 0.1f, getPosition().getY() - 0.1f, getPosition().getX() + 0.1f, getPosition().getY() + 0.1f);
}