#pragma once

#include "Obstacle.hpp"

class Map
{
	private:
		Vector2 playerSpawn;
		std::vector<Obstacle*> obstacles;

	public:
		~Map();

		void setPlayerSpawn(Vector2 playerSpawn);
		Vector2 getPlayerSpawn();

		void addObstacle(Obstacle* obstacle);
		void render();
};