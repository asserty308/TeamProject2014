#pragma once

#include "TransformCollidable.h"
#include "CollisionObserver.h"
#include "Netplayer.h"
#include "Sprite.hpp"


class Netplayer;

class NetRocket : public TransformCollidable{
public:
	NetRocket();
	NetRocket(Netplayer* owner, Vector2 postion, Vector2 forward);
	
	~NetRocket();

	virtual void CollisionDetected(TransformCollidable *other, Vector2 penetration);

	void update(Vector2 position, Vector2 forward);
	
	void playAnimation(int index, float speed, bool loop);

private:
	Netplayer* owner;

	Sprite *sprite;

	bool firstImpact;
};