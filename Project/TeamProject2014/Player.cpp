#include <SDL_opengl.h>
#include "Logger.hpp"
#include "InputObserver.h"
#include "CollisionObserver.h"
#include "Player.hpp"
#include "Timer.h"
#include "Game.hpp"
#include "SpriteRenderer.hpp"
#include "CircleBoundingBox.h"

const float Player::ACCELERATION = 38.f;
const float Player::TURN_SPEED = 100.f;

Player::Player(Vector2 position, Vector2 forward) : TransformCollidable(position, forward, Vector2(0.0f, 0.0f))
{
	isThrustKeyDown = isLeftKeyDown = isRightKeyDown = false;
	isRocketLaunched = renderRocket = false;
	
	g_pInputObserver->addListener(this);
	g_pCollisionObserver->addListener(this);

	boundingBox = new CircleBoundingBox(position, 10.0f);

	//create test sprite
	sprite = new Sprite("fighter4.png", position, Vector2(200.f, 150.f));

	rocket = nullptr;
}

Player::~Player(){
	delete sprite;
	delete boundingBox;
}

void Player::inputReceived(SDL_KeyboardEvent *key)
{
	if (key->keysym.sym == SDLK_w)
		isThrustKeyDown = (key->type == SDL_KEYDOWN);
	else if (key->keysym.sym == SDLK_a)
		isLeftKeyDown = (key->type == SDL_KEYDOWN);
	else if (key->keysym.sym == SDLK_d)
		isRightKeyDown = (key->type == SDL_KEYDOWN);
	else if (key->keysym.sym == SDLK_SPACE)
		isRocketLaunched = (key->type == SDL_KEYDOWN); //pressing 'space' will launch the rocket
}

void Player::CollisionDetected(TransformCollidable *other, Vector2 penetration){
	velocity += penetration * -1 * 15.0f;
}

void Player::update()
{
	if (!isRocketLaunched)
	{
		if (isThrustKeyDown)
			setAcceleration(forward * ACCELERATION);
		else
			setAcceleration(Vector2(0.0f, 0.0f));

		if (isLeftKeyDown && !isRightKeyDown)
			rotate(-TURN_SPEED * g_pTimer->getDeltaTime());
		else if (isRightKeyDown && !isLeftKeyDown)
			rotate(TURN_SPEED * g_pTimer->getDeltaTime());
	}

	handleRocket();

	if (getPosition().getX() < 0.f)
	{
		position.setX(0.f);
		velocity.setX(-velocity.getX() * .25f);
	}
	else if (getPosition().getX() > g_pGame->getWindowWidth())
	{
		position.setX(g_pGame->getWindowWidth());
		velocity.setX(-velocity.getX() * .25f);
	}

	if (getPosition().getY() < 0.f)
	{
		position.setY(0.f);
		velocity.setY(-velocity.getY() *.25f);
	}
	else if (getPosition().getY() > g_pGame->getWindowHeight())
	{
		position.setY(g_pGame->getWindowHeight());
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
		glVertex2f(getPosition().getX() + sin(angle) * 10.f, getPosition().getY() + cos(angle) * 10.f);
		angle = ((i + 1) * M_PI / 180.0) * 10.0;
		glVertex2f(getPosition().getX() + sin(angle) * 10.f, getPosition().getY() + cos(angle) * 10.f);
	}

	glVertex2f(getPosition().getX() + getForward().getX() * 5.f, getPosition().getY() + getForward().getY() * 5.f);
	glVertex2f(getPosition().getX() + getForward().getX() * 15.f, getPosition().getY() + getForward().getY() * 15.f);

	glEnd();

	if (renderRocket)
		rocket->render();
}

void Player::handleRocket()
{
	if (isRocketLaunched && rocket == nullptr)
	{
		rocket = new Rocket(getPosition(), getForward());
		rocket->setVelocity(getVelocity() * 2.f);
	}
	else if (isRocketLaunched && rocket != nullptr)
	{
		rocket->update();
		renderRocket = true;
	}
	else if (!isRocketLaunched && rocket != nullptr)
	{
		//if rocket is on screen, let it fly until it's out of screen
		if (rocket->getPosition().getX() > 0.f && rocket->getPosition().getX() < g_pGame->getWindowWidth() &&
			rocket->getPosition().getY() < g_pGame->getWindowHeight() && rocket->getPosition().getY() > 0.f)
		{
			rocket->update();
		}
		else
		{
			renderRocket = false;
			delete rocket;
			rocket = nullptr;
		}
	}
}