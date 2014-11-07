#pragma once
#include <vector>
#include <SDL_mixer.h>
#include "AudioBase.hpp"

class SoundPlayer /*: public AudioBase*/
{
	private:
		std::vector<Mix_Chunk*> sounds;

	public:
		SoundPlayer();
		~SoundPlayer();

		/*void play(bool loop);
		void stop();
		void loadFromFile(const char* path);*/
};

