#pragma once

#include "Vector2.hpp"

class BoundingBox
{
protected:
	Vector2 position;

public:
	BoundingBox(Vector2 position);

	Vector2 getPosition();

	void setPosition(Vector2 position);

};

