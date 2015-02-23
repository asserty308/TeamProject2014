#pragma once

#include <string>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SOIL.h>
#include <vector>
#include "Vector2.hpp"

class Sprite
{
	private:
		GLuint textureID;
		Vector2 position, dimensions;
		float angle;
		std::string filename;

		bool animationPlaying;
		bool loopAnimation;
		float sheetWidth;
		float animationTimer;
		int animFrameWidth;
		int indexOfActiveAnimation;
		int indexOfActiveAnimationFrame;
		float animationSpeed;
		std::vector<std::vector<int>> animations;

	public:
		Sprite();
		Sprite(char* path, Vector2 position, Vector2 dimensions, int numberOfFrames);
		~Sprite();

		void loadFromFile(const char* path);
		void render(int frameOverride = -1);

		void addAnimation(std::vector<int> frames);
		void playAnimation(int index, float speed, bool loop);

		int getAnimationIndex();

		void addAngle(float r);
		float getAngle();
		void setAngle(float a);

		void setPosition(Vector2 newPos);
		Vector2 getPosition();

		std::string getFilename();

		bool isPlayingAnimation();
};

