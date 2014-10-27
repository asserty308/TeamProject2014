#include "CollisionObserver.h"


CollisionObserver::CollisionObserver(void)
{
}

void CollisionObserver::addListener(TransformCollidable *l){
	listener.push_back(l);
}

void CollisionObserver::removeListener(TransformCollidable *l){
	listener.erase(std::find(listener.begin(), listener.end(), l));
}

void CollisionObserver::checkCollisionRoutine(){
	for(int i = 0; i < listener.size(); i++){
		for(int j = i; j < listener.size(); j++){
			if(i != j){
				
				checkForCollision(listener[i], listener[j]);
				
			}
		}
	}
}

void CollisionObserver::checkForCollision(TransformCollidable *lhs, TransformCollidable *rhs){
	CircleBoundingBox *b1 = static_cast<CircleBoundingBox*>(lhs->getBoundingBox());
	CircleBoundingBox *b2 = static_cast<CircleBoundingBox*>(rhs->getBoundingBox());

	if(b1 && b2){
		Vector2 p;
		if(checkCircleVsCircle(b1, b2, &p)){
			lhs->CollisionDetected(rhs, p * -1);
			rhs->CollisionDetected(lhs, p);
		}
	}
}

bool CollisionObserver::checkCircleVsCircle(CircleBoundingBox *lhs, CircleBoundingBox *rhs, Vector2 *p){
	float r1 = lhs->getRadius();
	float r2 = rhs->getRadius();

	Vector2 p1 = lhs->getPosition();
	Vector2 p2 = rhs->getPosition();
	Vector2 p3 = p2 - p1;

	
	float distanceSquared = p3.getX() * p3.getX() + p3.getY() * p3.getY();
	float radii = (r1 + r2);
	float radiiSquared = (r1 + r2) * (r1 + r2);

	if(distanceSquared < radiiSquared){
		float distance = std::sqrt(p3.getX() * p3.getX() + p3.getY() * p3.getY());
		float penetrationDistance = distance - radii;
		Vector2 penetrationVector = (p3 * (1 / distance)) * penetrationDistance;
		
		p->setX(penetrationVector.getX());
		p->setY(penetrationVector.getY());
		return true;
	}else{
		return false;
	}
}