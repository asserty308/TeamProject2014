#pragma once

#include "Sprite.hpp"
#include "Transform.hpp"
#include "NetRocket.h"

class NetRocket;

//TODO: Change Netplayer to TransformCollidable, so rockets can interact properly with them!

class Netplayer : public Transform{
public:
	Netplayer();
	Netplayer(Vector2 position, Vector2 forward);
	
	~Netplayer();

	void update(Vector2 pos, Vector2 forward, float angle, Vector2 rocketPos, Vector2 rocketForward);
	void render();

	void rocketDestroyed();

private:
	Sprite *sprite;
	NetRocket* netRocket;

};