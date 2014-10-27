#include "TransformCollidable.h"

TransformCollidable::TransformCollidable(Vector2 position, Vector2 forward, Vector2 velocity) :
	Transform(position, forward, velocity)
{
}


BoundingBox* TransformCollidable::getBoundingBox(){
	return boundingBox;
}

void TransformCollidable::updatePosition(float deltaTime){
	Transform::updatePosition(deltaTime);
	
	if(boundingBox){
		boundingBox->setPosition(position);
	}
}

