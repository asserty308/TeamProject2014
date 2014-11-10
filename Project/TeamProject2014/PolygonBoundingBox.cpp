#include "PolygonBoundingBox.h"


PolygonBoundingBox::PolygonBoundingBox(Vector2 position) : 
	BoundingBox(position){
}

void PolygonBoundingBox::addVertex(Vector2 Vertex){
	vertices.push_back(Vertex);
}

Vector2 PolygonBoundingBox::getVertex(int index){
	Vector2 v;
	try{
		v = vertices.at(index);
	}
	catch (std::out_of_range &e){
		g_pLogfile->log("Exception: Tried to access a non existent Vertex in PolygonBoundingBox");
	}
	return v;
}

int PolygonBoundingBox::getIndex(Vector2 v){
	return std::find(vertices.begin(), vertices.end(), v) - vertices.begin();
}