#pragma once

#include "Vector2.hpp"

#include <vector>

class Obstacle
{
	private:
		std::vector<Vector2> vertices;

	public:
		void addVertex(Vector2 vertex);
		void render();
};