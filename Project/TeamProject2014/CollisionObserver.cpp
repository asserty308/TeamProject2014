#include "CollisionObserver.h"
#include "SpriteRenderer.hpp"


CollisionObserver::CollisionObserver()
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
	{
		CircleBoundingBox *b1 = dynamic_cast<CircleBoundingBox*>(lhs->getBoundingBox());
		CircleBoundingBox *b2 = dynamic_cast<CircleBoundingBox*>(rhs->getBoundingBox());

		if (b1 && b2){
			Vector2 p;
			if (checkCircleVsCircle(b1, b2, &p)){
				lhs->CollisionDetected(rhs, p * -1);
				rhs->CollisionDetected(lhs, p);
			}
		}
	}

	{
		CircleBoundingBox *b1 = dynamic_cast<CircleBoundingBox*>(lhs->getBoundingBox());
		PolygonBoundingBox *b2 = dynamic_cast<PolygonBoundingBox*>(rhs->getBoundingBox());

		PolygonBoundingBox *b3 = dynamic_cast<PolygonBoundingBox*>(lhs->getBoundingBox());
		CircleBoundingBox *b4 = dynamic_cast<CircleBoundingBox*>(rhs->getBoundingBox());

		Vector2 p;
		if (b1 && b2){
			if (checkCircleVsPolygon(b1, b2, &p)){
				lhs->CollisionDetected(rhs, p * -1);
				rhs->CollisionDetected(lhs, p);
			}
		}else if (b3 && b4){
			if (checkCircleVsPolygon(b4, b3, &p)){
				lhs->CollisionDetected(rhs, p * -1);
				rhs->CollisionDetected(lhs, p);
			}
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

bool CollisionObserver::checkCircleVsPolygon(CircleBoundingBox *lhs, PolygonBoundingBox *rhs, Vector2 *p){
	
	Vector2 penetration;

	Vector2 c = lhs->getPosition();
	
	//placeholder
	Vector2 v;
	Vector2 t;

	//extent of the Circle in x- and y-direction
	Vector2 cLeft = c - Vector2(lhs->getRadius(), 0);
	Vector2 cRight = c + Vector2(lhs->getRadius(), 0);
	Vector2 cTop = c - Vector2(0, lhs->getRadius());
	Vector2 cBot = c + Vector2(0, lhs->getRadius());

	Vector2 cLeftOnX = Vector2::projectVector(cLeft, xAxis);
	Vector2 cRightOnX = Vector2::projectVector(cRight, xAxis);
	Vector2 cTopOnY = Vector2::projectVector(cTop, yAxis);
	Vector2 cBotOnY = Vector2::projectVector(cBot, yAxis);

	//extent of polygon in x- and y-direction
	Vector2 vMaxX = Vector2(0, 0);
	Vector2 vMinX = Vector2(0, 0);
	Vector2 vMaxY = Vector2(0, 0);
	Vector2 vMinY = Vector2(0, 0);

	//Polygonvertex that is the nearest to the Circle
	Vector2 nearest;
	
	for (int j = 0; j < rhs->getVerticesCount(); j++){
		t = rhs->getVertex(j);
		Vector2 distance = t - c;
		if (distance.getX() * distance.getX() + distance.getY() * distance.getY() <
			(nearest - c).getX() * (nearest - c).getX() + (nearest - c).getY() * (nearest - c).getY()){
			nearest = t;
		}
	}

	for (int i = 0; i < rhs->getVerticesCount(); i++){
		v = rhs->getVertex(i);
		if (v.getX() > vMaxX.getX()){
			vMaxX = v;
		}
		if (v.getX() < vMaxX.getX() || vMinX.getX() == 0.0f){
			vMinX = v;
		}
		if (v.getY() > vMaxY.getY()){
			vMaxY = v;
		}
		if (v.getY() < vMaxY.getY() || vMinY.getY() == 0.0f){
			vMinY = v;
		}
	}

	Vector2 vProjMaxX = Vector2::projectVector(vMaxX, xAxis);;
	Vector2 vProjMinX = Vector2::projectVector(vMinX, xAxis);;
	Vector2 vProjMaxY = Vector2::projectVector(vMaxY, yAxis);;
	Vector2 vProjMinY = Vector2::projectVector(vMinY, yAxis);;

	//Axis that runs through the nearest vertex and the circle center
	Vector2 vToCAxis = nearest - c;
	Vector2 vToCAxisNorm = vToCAxis;
	vToCAxisNorm.normalize();


	//Polygonvertices to be projected upon the axis
	int neighbor1 = (rhs->getIndex(nearest) + 1) % rhs->getVerticesCount();
	int neighbor2 = (rhs->getIndex(nearest) - 1) < 0 ? rhs->getVerticesCount()-1 : (rhs->getIndex(nearest) - 1);

	Vector2 nearestProj = Vector2::projectVector(nearest, vToCAxis);
	Vector2 nearestProjMin = Vector2::projectVector(rhs->getVertex(neighbor1), vToCAxis);
	Vector2 nearestProjMax = Vector2::projectVector(rhs->getVertex(neighbor2), vToCAxis);

	//Circlevertices to be projected upon the axis
	Vector2 cNearOnAx = c + (vToCAxisNorm * lhs->getRadius());
	Vector2 cFarOnAx = c - (vToCAxisNorm * lhs->getRadius());
	Vector2 cNearOnProjAx = Vector2::projectVector(cNearOnAx, vToCAxis);
	Vector2 cFarOnProjAx = Vector2::projectVector(cFarOnAx, vToCAxis);

	//Check on x- and y-Axis if overlapping occurs
	if (cRightOnX.getX() > vMinX.getX() && cLeftOnX.getX() < vMaxX.getX() &&
		cBotOnY.getY() > vMinY.getY() && cTopOnY.getY() < vMaxY.getY()){

		Vector2 penCan1 = c.getX() < vProjMinX.getX() ? cRightOnX - vProjMinX : cLeftOnX - vProjMaxX;
		Vector2 penCan2 = c.getY() < vProjMinY.getY() ? cBotOnY - vProjMinY : cTopOnY - vProjMaxY;

		penetration = std::abs(penCan1.getX()) < std::abs(penCan2.getY()) ? penCan1 : penCan2;

		//Check vertex overlap
		if ((nearestProj.getX() > cFarOnProjAx.getX() && nearestProj.getX() < cNearOnProjAx.getX()) ||
			(nearestProjMax.getX() < cNearOnProjAx.getX() && nearestProjMin.getX() > cFarOnProjAx.getX()) ||
			(nearestProjMin.getX() < cNearOnProjAx.getX() && nearestProjMax.getX() > cFarOnProjAx.getX())){

		    Vector2 penCan3 = cNearOnProjAx - nearestProj;

			penetration = std::abs(penetration.getX()) < std::abs(penCan3.getX()) && std::abs(penetration.getY()) < std::abs(penCan3.getY()) ? penetration : penCan3;
			
			p->setX(penetration.getX());
			p->setY(penetration.getY());

			return true;
		
		}

	}

	return false;
}