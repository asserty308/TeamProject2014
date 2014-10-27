#include "CircleBoundingBox.h"


CircleBoundingBox::CircleBoundingBox(Vector2 position, float radius) :
	BoundingBox(position){
		this->radius = radius;
}


