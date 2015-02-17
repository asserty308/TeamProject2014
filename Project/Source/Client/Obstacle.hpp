#pragma once

#include "Vector2.hpp"
#include "PolygonBoundingBox.h"
#include "CollisionObserver.h"
#include <vector>
#include <SOIL.h>
#include <SDL_opengl.h>

class Obstacle :
	public TransformCollidable
{
	private:
		std::vector<Vector2> vertices;
		GLuint* textureID;
		GLuint* edgeTextureID;

	public:
		Obstacle(GLuint* textureID, GLuint* edgeTextureID);

		~Obstacle(){
			delete boundingBox;
		}

		void addVertex(Vector2 vertex);
		void render();

		virtual void CollisionDetected(TransformCollidable *other, Vector2 projection){

		}
};