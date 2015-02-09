#pragma once

#include "NetRocket.h"
#include "Game.hpp"

NetRocket::NetRocket() : TransformCollidable(Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f)){
	// TODO: delete?
}

NetRocket::NetRocket(Netplayer* owner, Vector2 position, Vector2 forward) : TransformCollidable(position, forward, Vector2(1.0f, 1.0f)){
	g_pCollisionObserver->addListener(this);

	boundingBox = new CircleBoundingBox(position, 10.0f);

	//create sprite
	sprite = new Sprite("Sprites\\new_rocket.png", position, Vector2(14.f, 24.f));

	this->owner = owner;
}

NetRocket::~NetRocket(){
	delete sprite;
	delete boundingBox;
}

void NetRocket::CollisionDetected(TransformCollidable *other, Vector2 penetration){
	if (other == owner){
		return;
	}

	owner->rocketDestroyed();
}

void NetRocket::update(Vector2 position, Vector2 forward){
	setPosition(position);
	setForward(forward);

	sprite->setPosition(position);
	sprite->setAngle(angleFromVector<float>(forward));
}

/*
void NetRocket::render()
{
	if (position.getX() > 0 && position.getX() < g_pGame->getWindowWidth() &&
		position.getY() > 0 && position.getY() < g_pGame->getWindowHeight() ){
	
		glColor3f(0.f, 0.f, 1.f);
		glLineWidth(2.f);

		glBegin(GL_POLYGON);
		glVertex2f(position.getX() + forward.getX() * 10.f, position.getY() + forward.getY() * 10.f);
		glVertex2f(position.getX() - forward.getX() * 10.f - getRight().getX() * 6.f, position.getY() - forward.getY() * 10.f - getRight().getY() * 6.f);
		glVertex2f(position.getX() - forward.getX() * 6.f, position.getY() - forward.getY() * 6.f);
		glVertex2f(position.getX() - forward.getX() * 10.f + getRight().getX() * 6.f, position.getY() - forward.getY() * 10.f + getRight().getY() * 6.f);
		glEnd();
	}
}
*/


	