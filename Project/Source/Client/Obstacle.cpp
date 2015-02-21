#include <SDL_opengl.h>

#include "Obstacle.hpp"
#include "Game.hpp"

#define EDGE_WIDTH 3.f

Obstacle::Obstacle(GLuint* textureID, GLuint* edgeTextureID) : TransformCollidable(Vector2(0, 0), Vector2(0, 0), Vector2(0, 0)){
	
	boundingBox = new PolygonBoundingBox(Vector2(0, 0));
	g_pCollisionObserver->addListener(this);

	this->textureID = textureID;
	this->edgeTextureID = edgeTextureID;

}

void Obstacle::addVertex(Vector2 vertex)
{
	vertices.push_back(vertex);
	static_cast<PolygonBoundingBox*>(boundingBox)->addVertex(vertex);
}

void Obstacle::render()
{
	glEnable(GL_TEXTURE_2D);
	

	// draw fill shape

	glBindTexture(GL_TEXTURE_2D, *textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBegin(GL_POLYGON);
	
	for (Vector2 i : vertices)
	{
		glTexCoord2f(i.getX() / g_pGame->getWindowWidth() * 4.f, i.getY() / g_pGame->getWindowHeight() * 4.f);
		glVertex2f(i.getX(), i.getY());
	}

	glEnd();


	// draw edge

	glBindTexture(GL_TEXTURE_2D, *edgeTextureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	for (unsigned int i = 0; i < vertices.size(); ++i)
	{
		glBegin(GL_POLYGON);

		Vector2 a(vertices[i].getX(), vertices[i].getY());
		Vector2 b(vertices[(i + 1) % vertices.size()].getX(), vertices[(i + 1) % vertices.size()].getY());
		Vector2 v(b.getX() - a.getX(), b.getY() - a.getY());
		
		Vector2 _a(-v.getY(), v.getX());
		_a.normalize();

		Vector2 _b(v.getY(), -v.getX());
		_b.normalize();

		Vector2 v1 = a + _a * EDGE_WIDTH;
		Vector2 v2 = a + _b * EDGE_WIDTH;
		Vector2 v3 = b + _a * EDGE_WIDTH;
		Vector2 v4 = b + _b * EDGE_WIDTH;

		float texSquare = v.getLength() / (EDGE_WIDTH * 4.f/*2.f*/);

		glTexCoord2f(0.f, 0.f);
		glVertex2f(v1.getX(), v1.getY());

		glTexCoord2f(0.f, 1.f);
		glVertex2f(v2.getX(), v2.getY());

		glTexCoord2f(texSquare, 1.f);
		glVertex2f(v4.getX(), v4.getY());

		glTexCoord2f(texSquare, 0.f);
		glVertex2f(v3.getX(), v3.getY());

		glEnd();
	}

}