#pragma once

#include <string>

#include "Map.hpp"

class MapParser
{
	private:

	public:
		static Map *loadMap(std::string filename);
};