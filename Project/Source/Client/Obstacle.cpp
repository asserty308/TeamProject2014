#include <SDL_opengl.h>

#include "Obstacle.hpp"
#include "Game.hpp"

Obstacle::Obstacle(GLuint* textureID) : TransformCollidable(Vector2(0, 0), Vector2(0, 0), Vector2(0, 0)){
	
	boundingBox = new PolygonBoundingBox(Vector2(0, 0));
	g_pCollisionObserver->addListener(this);

	this->textureID = textureID;

}

void Obstacle::addVertex(Vector2 vertex)
{
	vertices.push_back(vertex);
	static_cast<PolygonBoundingBox*>(boundingBox)->addVertex(vertex);
}

void Obstacle::render()
{
	glEnable(GL_TEXTURE_2D);
	
	//glColor3f(0.f, 0.f, 1.f);
	glBindTexture(GL_TEXTURE_2D, *textureID);

	glBegin(GL_POLYGON);
	
	for (std::vector<Vector2>::iterator i = vertices.begin(); i != vertices.end(); ++i){
		glTexCoord2f((*i).getX() / g_pGame->getWindowWidth(), (*i).getY() / g_pGame->getWindowHeight());
		glVertex2f((*i).getX(), (*i).getY());
	}

	glEnd();

}