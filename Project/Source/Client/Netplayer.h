#pragma once

#include "Sprite.hpp"
#include "Transform.hpp"
#include "NetRocket.h"
#include "CollisionObserver.h"
#include "MathUtil.h"
#include "Timer.h"

#define EXPECTEDTICKRATE 0.066


struct NetplayerData{
	Vector2 pos;
	Vector2 forward;
	float angle;
	Vector2 rocketPos;
	Vector2 rocketForward;
	bool isDead;
};


class NetRocket;

class Netplayer : public TransformCollidable{
public:
	Netplayer();
	Netplayer(std::string name, Vector2 position, Vector2 forward);
	
	~Netplayer();

	virtual void CollisionDetected(TransformCollidable *other, Vector2 penetration);

	void update();
	void render();

	void updateNetData(Vector2 pos, Vector2 forward, float angle, Vector2 rocketPos, Vector2 rocketForward, bool isDead);
	void rocketDestroyed();

	bool getIsDead();

	Sprite *getSprite();

	int getScore();
	void setScore(int score);

private:
	Sprite *sprite;
	NetRocket* netRocket;
	bool isDead;
	std::string name;
	int score;

	NetplayerData frontHistoryCache;
	NetplayerData backHistoryCache;
	float updateElapsed;

};