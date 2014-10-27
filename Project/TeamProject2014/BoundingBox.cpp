#include "BoundingBox.h"


BoundingBox::BoundingBox(Vector2 position)
{
	this->position = position;
}

void BoundingBox::setPosition(Vector2 position){
	this->position = position;
}

Vector2 BoundingBox::getPosition(){
	return position;
}
