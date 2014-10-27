#pragma once
#include "Transform.hpp"
#include "BoundingBox.h"

class TransformCollidable :
	public Transform
{
protected:
	BoundingBox *boundingBox;

public:
	TransformCollidable(Vector2 position, Vector2 forward, Vector2 velocity);

	virtual BoundingBox* getBoundingBox();

	virtual void updatePosition(float deltaTime);

	virtual void CollisionDetected(TransformCollidable *other, Vector2 projection) = 0;	
};

