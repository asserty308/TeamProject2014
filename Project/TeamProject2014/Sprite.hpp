#pragma once

#include <SDL.h>
#include <SDL_opengl.h>
#include <SOIL.h>
#include "Vector2.hpp"

class Sprite
{
	private:
		GLuint textureID;
		Vector2 position, dimensions;
		unsigned char* img;

	public:
		Sprite();
		Sprite(const char* path, Vector2 position, Vector2 dimensions);
		~Sprite();

		void loadFromFile(const char* path);
		void render();
};

