#pragma once

#include "Sprite.hpp"
#include "Transform.hpp"

class Netplayer : public Transform{
public:
	Netplayer();
	Netplayer(Vector2 position, Vector2 forward);
	
	~Netplayer();

	void update(Vector2 pos);
	void render();

private:
	Sprite *sprite;

};