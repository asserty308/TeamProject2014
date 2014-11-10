#pragma once
#include "BoundingBox.h"
#include "Logger.hpp"
#include <vector>
class PolygonBoundingBox :
	public BoundingBox
{
private:
	std::vector<Vector2> vertices;
	
public:
	PolygonBoundingBox(Vector2 position);
	
	Vector2 getVertex(int index);
	int getIndex(Vector2 v);
	
	void addVertex(Vector2 v);
		

	int getVerticesCount(){
		return vertices.size();
	}

	virtual Vector2 getPosition(){
		return position;
	};

};

