#pragma once
#include "transformcollidable.h"
class DebugCollider :
	public TransformCollidable
{
private:
	float rad;

public:
	DebugCollider(Vector2 position, Vector2 forward, float rad);
	~DebugCollider();

	virtual void CollisionDetected(TransformCollidable *other, Vector2 projection);
	
	void render();
};

