#include "Logger.hpp"
#include "Rocket.hpp"
#include "AudioController.hpp"
#include "CollisionObserver.h"
#include "AudioFiles.hpp"
#include "MathUtil.h"
#include <math.h>

const float Rocket::SPEED = 400.f;
const float Rocket::TURN_SPEED = 160.f;
const float Rocket::TURN_ACCELERATION = 50.f;

Rocket::Rocket(Player* owner, Vector2 position, Vector2 forward) : TransformCollidable(position, forward, Vector2(0.f, 0.f))
{
	g_pInputObserver->addListener(this);
	g_pCollisionObserver->addListener(this);

	boundingBox = new CircleBoundingBox(position, 10.0f);

	controllable = true;
	isLeftKeyDown = isRightKeyDown = false;

	torque = 0.0;

	this->owner = owner;

	//create sprite
	sprite = new Sprite("Sprites\\new_rocket.png", position, Vector2(14.f, 24.f));

	g_pAudioController->playSound(SoundFiles::ROCKET, false);
}

Rocket::~Rocket()
{
	delete sprite;
	delete boundingBox;

	g_pInputObserver->removeListener(this);
	g_pCollisionObserver->removeListener(this);

	g_pAudioController->stopSoundByFile(SoundFiles::ROCKET);
}

void Rocket::inputReceived(SDL_KeyboardEvent *key)
{
	if (!controllable)
		return;

	if (key->type == SDL_KEYDOWN)
	{
		float playerAngle = atan2(owner->getForward().getY(), owner->getForward().getX()) / M_PI * 180.0f;

		if (key->keysym.sym == SDLK_a && !isLeftKeyDown)
		{
			torque += -TURN_SPEED * g_pTimer->getDeltaTime();
			isLeftKeyDown = true;
		}
		else if (key->keysym.sym == SDLK_d && !isRightKeyDown)
		{
			torque += TURN_SPEED * g_pTimer->getDeltaTime();
			isRightKeyDown = true;
		}
	}
	else if (key->type == SDL_KEYUP)
	{
		if (key->keysym.sym == SDLK_SPACE)
			controllable = false;
		else if (key->keysym.sym == SDLK_a){
			isLeftKeyDown = false;
			torque = 0.0f;
		} else if (key->keysym.sym == SDLK_d){
			isRightKeyDown = false;
			torque = 0.0f;
		}
	}
}

void Rocket::CollisionDetected(TransformCollidable *other, Vector2 penetration){
	if (other == owner){
		return;
	}

	owner->rocketDestroyed();
}

bool Rocket::getControllable()
{
	return controllable;
}

void Rocket::update()
{
	//setAcceleration(forward * TURN_ACCELERATION);

	// make sure the velocity of the rocket is constant
	// and always towards the current forward vector
	rotate(torque);
	setVelocity(forward * SPEED);

	updatePosition(g_pTimer->getDeltaTime());
	sprite->setPosition(position);
	sprite->setAngle(angleFromVector<float>(forward));
}

/*
void Rocket::render()
{
	glColor3f(0.f, 0.f, 1.f);
	glLineWidth(2.f);

	glBegin(GL_POLYGON);
	glVertex2f(position.getX() + forward.getX() * 10.f, position.getY() + forward.getY() * 10.f);
	glVertex2f(position.getX() - forward.getX() * 10.f - getRight().getX() * 6.f, position.getY() - forward.getY() * 10.f - getRight().getY() * 6.f);
	glVertex2f(position.getX() - forward.getX() * 6.f, position.getY() - forward.getY() * 6.f);
	glVertex2f(position.getX() - forward.getX() * 10.f + getRight().getX() * 6.f, position.getY() - forward.getY() * 10.f + getRight().getY() * 6.f);
	glEnd();
	
	glBegin(GL_LINES);

	for (int i = 0; i < 36; ++i)
	{
		float angle = (i * M_PI / 180.0) * 10.0;
		glVertex2f(getPosition().getX() + sin(angle) * r, getPosition().getY() + cos(angle) * r);
		angle = ((i + 1) * M_PI / 180.0) * 10.0;
		glVertex2f(getPosition().getX() + sin(angle) * r, getPosition().getY() + cos(angle) * r);
	}

	glEnd();
}
*/