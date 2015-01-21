#pragma once

#include "NetRocket.h"

NetRocket::NetRocket() : TransformCollidable(Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f)){

}

NetRocket::NetRocket(Netplayer* owner, Vector2 postion, Vector2 forward) : TransformCollidable(position, forward, Vector2(1.0f, 1.0f)){
	g_pCollisionObserver->addListener(this);

	boundingBox = new CircleBoundingBox(position, 10.0f);

	this->owner = owner;
}

NetRocket::~NetRocket(){
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
}

void NetRocket::render(){
	glColor3f(0.f, 0.f, 1.f);
	glLineWidth(2.f);

	glBegin(GL_POLYGON);
	glVertex2f(position.getX() + forward.getX() * 10.f, position.getY() + forward.getY() * 10.f);
	glVertex2f(position.getX() - forward.getX() * 10.f - getRight().getX() * 6.f, position.getY() - forward.getY() * 10.f - getRight().getY() * 6.f);
	glVertex2f(position.getX() - forward.getX() * 6.f, position.getY() - forward.getY() * 6.f);
	glVertex2f(position.getX() - forward.getX() * 10.f + getRight().getX() * 6.f, position.getY() - forward.getY() * 10.f + getRight().getY() * 6.f);
	glEnd();
}


	