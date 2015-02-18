#pragma once

#include "Obstacle.hpp"

class Map
{
	private:
		Vector2 playerSpawn;
		std::vector<Obstacle*> obstacles;
		GLuint textureID;
		GLuint edgeTextureID;

	public:
		Map();
		~Map();

		void setPlayerSpawn(Vector2 playerSpawn);
		Vector2 getPlayerSpawn();

		GLuint* getTextureID(){
			return &textureID;
		}

		GLuint* getEdgeTextureID(){
			return &edgeTextureID;
		}

		void addObstacle(Obstacle* obstacle);
		void render();
};