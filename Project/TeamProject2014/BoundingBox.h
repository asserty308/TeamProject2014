#pragma once

#include "Vector2.hpp"

class BoundingBox
{
protected:
	Vector2 position;

public:
	BoundingBox(Vector2 position);

	virtual Vector2 getPosition() = 0;

	void setPosition(Vector2 position);

};

