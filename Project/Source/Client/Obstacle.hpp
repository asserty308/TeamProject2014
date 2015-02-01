#pragma once

#include "Vector2.hpp"
#include "PolygonBoundingBox.h"
#include "CollisionObserver.h"
#include <vector>

class Obstacle :
	public TransformCollidable
{
	private:
		std::vector<Vector2> vertices;

	public:
		Obstacle() : TransformCollidable(Vector2(0, 0), Vector2(0, 0), Vector2(0, 0)){
			boundingBox = new PolygonBoundingBox(Vector2(0, 0));
			g_pCollisionObserver->addListener(this);
		}

		~Obstacle(){
			delete boundingBox;
		}

		void addVertex(Vector2 vertex);
		void render();

		virtual void CollisionDetected(TransformCollidable *other, Vector2 projection){

		}
};