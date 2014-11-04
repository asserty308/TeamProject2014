#include "Logger.hpp"
#include "Rocket.hpp"

const float Rocket::SPEED = 400.f;
//const float Rocket::TURN_SPEED = 60.f;
//const float Rocket::TURN_ACCELERATION = 50.f;

Rocket::Rocket(Vector2 position, Vector2 forward) : Transform(position, forward, Vector2(0.f, 0.f))
{
	g_pInputObserver->addListener(this);

	controllable = true;
	isLeftKeyDown = isRightKeyDown = false;
}

Rocket::~Rocket()
{
	g_pInputObserver->removeListener(this);
}

void Rocket::inputReceived(SDL_KeyboardEvent *key)
{
	if (!controllable)
		return;

	if (key->type == SDL_KEYDOWN)
	{
		if (key->keysym.sym == SDLK_a && !isLeftKeyDown)
		{
			rotate(/*-TURN_SPEED * g_pTimer->getDeltaTime()*/-45.f);
			isLeftKeyDown = true;
		}
		else if (key->keysym.sym == SDLK_d && !isRightKeyDown)
		{
			rotate(/*-TURN_SPEED * g_pTimer->getDeltaTime()*/45.f);
			isRightKeyDown = true;
		}
	}
	else if (key->type == SDL_KEYUP)
	{
		if (key->keysym.sym == SDLK_SPACE)
			controllable = false;
		else if (key->keysym.sym == SDLK_a)
			isLeftKeyDown = false;
		else if (key->keysym.sym == SDLK_d)
			isRightKeyDown = false;
	}
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
	setVelocity(forward * SPEED);

	updatePosition(g_pTimer->getDeltaTime());
}

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

	/*
	glBegin(GL_LINES);

	for (int i = 0; i < 36; ++i)
	{
		float angle = (i * M_PI / 180.0) * 10.0;
		glVertex2f(getPosition().getX() + sin(angle) * r, getPosition().getY() + cos(angle) * r);
		angle = ((i + 1) * M_PI / 180.0) * 10.0;
		glVertex2f(getPosition().getX() + sin(angle) * r, getPosition().getY() + cos(angle) * r);
	}

	glEnd();
	*/
}