#include "Map.hpp"

Map::Map()
{
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	textureID = SOIL_load_OGL_texture("Sprites\\metal_floor.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	edgeTextureID = SOIL_load_OGL_texture("Sprites\\obstacle_edge.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);

	if (textureID == 0 || edgeTextureID == 0)
		g_pLogfile->fLog("SOIL loading error: %s", SOIL_last_result());

}

Map::~Map(){
	for (Obstacle* o : obstacles){
		delete o;
	}
}

void Map::setPlayerSpawn(Vector2 playerSpawn)
{
	this->playerSpawn = playerSpawn;
}

Vector2 Map::getPlayerSpawn()
{
	return playerSpawn;
}

void Map::addObstacle(Obstacle* obstacle)
{
	obstacles.push_back(obstacle);
}

void Map::render()
{
	for (std::vector<Obstacle*>::iterator i = obstacles.begin(); i != obstacles.end(); ++i)
		(*i)->render();
}