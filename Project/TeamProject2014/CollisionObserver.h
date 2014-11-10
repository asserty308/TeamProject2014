#pragma once
#include "singleton.hpp"
#include "TransformCollidable.h"
#include "CircleBoundingBox.h"
#include "PolygonBoundingBox.h"
#include <vector>

#define g_pCollisionObserver CollisionObserver::Get()

class CollisionObserver :
	public Singleton<CollisionObserver>
{
public:
	CollisionObserver();

	void addListener(TransformCollidable *l);
	void removeListener(TransformCollidable *l);

	void checkCollisionRoutine();

	void setxAxis(Vector2 xAxis){
		this->xAxis = xAxis;
	}

	void setyAxis(Vector2 yAxis){
		this->yAxis = yAxis;
	}

private:
	std::vector<TransformCollidable*> listener;

	Vector2 xAxis;
	Vector2 yAxis;
	
	void checkForCollision(TransformCollidable *lhs, TransformCollidable *rhs);
	bool checkCircleVsCircle(CircleBoundingBox *lhs, CircleBoundingBox *rhs, Vector2 *p);
	bool checkCircleVsPolygon(CircleBoundingBox *lhs, PolygonBoundingBox *rhs, Vector2 *p);

};

