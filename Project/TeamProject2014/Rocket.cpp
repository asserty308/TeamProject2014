#include "Rocket.hpp"

const float Rocket::TURN_SPEED = 60.f;
const float Rocket::TURN_ACCELERATION = 50.f;

Rocket::Rocket(Vector2 position, Vector2 forward) : Transform(position, forward, Vector2(0.f, 0.f))
{
	g_pInputObserver->addListener(this);

	controllable = true;
	leftKeyDown = false;
	rightKeyDown = false;
}

Rocket::~Rocket()
{
	g_pInputObserver->removeListener(this);
}

void Rocket::inputReceived(SDL_KeyboardEvent *key)
{
	switch (key->keysym.sym)
	{
		case SDLK_a:
			leftKeyDown = (key->type == SDL_KEYDOWN);
			break;
		case SDLK_d:
			rightKeyDown = (key->type == SDL_KEYDOWN);
			break;
		case SDLK_SPACE:
			if (key->type == SDL_KEYUP)
				controllable = false;
			break;
		default:
			break;
	}
}

void Rocket::update()
{
	if (controllable)
	{
		if (leftKeyDown && !rightKeyDown)
		{
			rotate(-TURN_SPEED * g_pTimer->getDeltaTime());
		}
		else if (!leftKeyDown && rightKeyDown)
		{
			rotate(TURN_SPEED * g_pTimer->getDeltaTime());
		}
	}

	setAcceleration(forward * TURN_ACCELERATION);

	updatePosition(g_pTimer->getDeltaTime());
}

void Rocket::render()
{
	float r = 5;

	glColor3f(0.f, 0.f, 1.f);

	glLineWidth(2.f);

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