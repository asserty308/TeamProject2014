#include <SDL_opengl.h>

#include "Obstacle.hpp"

void Obstacle::addVertex(Vector2 vertex)
{
	vertices.push_back(vertex);
}

void Obstacle::render()
{
	glColor3f(1.f, .5f, 0.f);

	glBegin(GL_POLYGON);

	for (std::vector<Vector2>::iterator i = vertices.begin(); i != vertices.end(); ++i)
		glVertex2f((*i).getX(), (*i).getY());

	glEnd();

	glColor3f(1.f, 0.f, 0.f);
	glLineWidth(3.f);

	glBegin(GL_LINES);

	for (unsigned int i = 0; i < vertices.size(); ++i)
	{
		glVertex2f(vertices[i].getX(), vertices[i].getY());

		if (i + 1 < vertices.size())
			glVertex2f(vertices[i + 1].getX(), vertices[i + 1].getY());
		else
			glVertex2f(vertices[0].getX(), vertices[0].getY());
	}

	glEnd();

	
}