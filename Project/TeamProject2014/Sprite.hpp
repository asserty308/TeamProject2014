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
		float angle;
		unsigned char* img;

	public:
		Sprite();
		Sprite(const char* path, Vector2 position, Vector2 dimensions);
		~Sprite();

		void loadFromFile(const char* path);
		void render();

		void addAngle(float r);
		void setPosition(Vector2 newPos);
		Vector2 getPosition();
};

