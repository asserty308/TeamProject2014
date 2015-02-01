#include "DebugCollider.h"
#include "CircleBoundingBox.h"
#include "CollisionObserver.h"
#include <SDL_opengl.h>
#include <SDL_stdinc.h>
#include <math.h>

DebugCollider::DebugCollider(Vector2 position, Vector2 forward, float rad) : TransformCollidable(position, forward, Vector2(0.0f, 0.0f))
{
	this->rad = rad;
	boundingBox = new CircleBoundingBox(position, rad);
	g_pCollisionObserver->addListener(this);
}

DebugCollider::~DebugCollider(){
	delete boundingBox;
}

void DebugCollider::CollisionDetected(TransformCollidable *other, Vector2 projection){

}

void DebugCollider::render(){
	glColor3f(0.f, 1.f, 0.f);
	
	glLineWidth(2.f);

	glBegin(GL_LINES);

	for (int i = 0; i < 36; ++i)
	{
		float angle = (i * M_PI / 180.0) * rad;
		glVertex2f(getPosition().getX() + sin(angle) * rad, getPosition().getY() + cos(angle) * rad);
		angle = ((i + 1) * M_PI / 180.0) * rad;
		glVertex2f(getPosition().getX() + sin(angle) * rad, getPosition().getY() + cos(angle) * rad);
	}

	glEnd();
}