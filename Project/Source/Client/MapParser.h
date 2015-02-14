#pragma once

#include <string>

#include "Map.hpp"
#include <SOIL.h>

class MapParser
{
	private:

	public:
		static Map *loadMap(std::string filename);
};