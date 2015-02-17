#include <tinyxml2.h>

#include <sstream>

#include "Logger.hpp"
#include "MapParser.h"

using namespace tinyxml2;

Map *MapParser::loadMap(std::string filename)
{

	XMLDocument *doc = new XMLDocument;

	int returnCode = doc->LoadFile(filename.c_str());

	if (returnCode != XML_SUCCESS)
	{
		std::stringstream s;
		s << "ERROR: Failed to open requested map file: " << filename << " (error code: " << returnCode << ")";
		g_pLogfile->fLog(s.str().c_str());
		return nullptr;
	}

	Map *map = new Map;

	XMLElement *root = doc->RootElement();

	if (root)
	{
		XMLElement *element = root->FirstChildElement();

		while (element)
		{
			if (strcmp(element->Name(), "PlayerSpawn") == 0)
			{
				float x, y;
				element->QueryFloatAttribute("x", &x);
				element->QueryFloatAttribute("y", &y);
				map->setPlayerSpawn(Vector2(x, y));
			}
			else if (strcmp(element->Name(), "Obstacle") == 0)
			{
				Obstacle* obstacle = new Obstacle(map->getTextureID(), map->getEdgeTextureID());

				XMLElement *vertexElement = element->FirstChildElement();

				while (vertexElement)
				{
					if (strcmp(vertexElement->Name(), "Vertex") == 0)
					{
						float x, y;
						vertexElement->QueryFloatAttribute("x", &x);
						vertexElement->QueryFloatAttribute("y", &y);
						obstacle->addVertex(Vector2(x, y));
					}

					vertexElement = vertexElement->NextSiblingElement();
				}

				map->addObstacle(obstacle);
			}

			element = element->NextSiblingElement();
		}

		return map;
	}

	delete map;
	return nullptr;
}