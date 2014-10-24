#include "Map.hpp"

void Map::setPlayerSpawn(Vector2 playerSpawn)
{
	this->playerSpawn = playerSpawn;
}

Vector2 Map::getPlayerSpawn()
{
	return playerSpawn;
}

void Map::addObstacle(Obstacle obstacle)
{
	obstacles.push_back(obstacle);
}

void Map::render()
{
	for (std::vector<Obstacle>::iterator i = obstacles.begin(); i != obstacles.end(); ++i)
		(*i).render();
}