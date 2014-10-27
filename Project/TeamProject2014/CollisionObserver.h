#pragma once
#include "singleton.hpp"
#include "TransformCollidable.h"
#include "CircleBoundingBox.h"
#include <vector>

#define g_pCollisionObserver CollisionObserver::Get()

class CollisionObserver :
	public Singleton<CollisionObserver>
{
public:
	CollisionObserver(void);

	void addListener(TransformCollidable *l);
	void removeListener(TransformCollidable *l);

	void checkCollisionRoutine();

private:
	std::vector<TransformCollidable*> listener;
	
	void checkForCollision(TransformCollidable *lhs, TransformCollidable *rhs);
	bool checkCircleVsCircle(CircleBoundingBox *lhs, CircleBoundingBox *rhs, Vector2 *p);

};

