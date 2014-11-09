#pragma once
#include <map>
#include <SDL_mixer.h>
#include "AudioBase.hpp"

class SoundPlayer : public AudioBase
{
	private:
		Uint8 maxChannels, usedChannels;
		std::map<const char*, Mix_Chunk*> sounds;

	public:
		SoundPlayer();
		~SoundPlayer();

		void play(bool loop);
		void stop();
		void loadFromFile(const char* path);
		void removeSoundByFile(const char* path);
};

