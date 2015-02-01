#pragma once
#include "Transform.hpp"
#include "BoundingBox.h"

#include <string>

class TransformCollidable :
	public Transform
{
protected:
	BoundingBox *boundingBox;

	std::string tag;

public:
	TransformCollidable(Vector2 position, Vector2 forward, Vector2 velocity);

	void setPosition(Vector2 position);

	void setTag(std::string t){
		tag.assign(t);
	}

	std::string getTag(){
		return tag;
	}

	virtual BoundingBox* getBoundingBox();

	virtual void updatePosition(float deltaTime);

	virtual void CollisionDetected(TransformCollidable *other, Vector2 projection) = 0;	
};

