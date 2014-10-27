#pragma once
#include "boundingbox.h"
class CircleBoundingBox :
	public BoundingBox
{
private:
	float radius;

public:
	CircleBoundingBox(Vector2 position, float radius);

	float getRadius(){
		return radius;
	}
};

