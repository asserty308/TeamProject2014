#pragma once
#include <map>
#include <array>
#include <SDL_mixer.h>
#include <string>

#define MAX_CHANNELS 10

class SoundPlayer
{
	private:
		Uint8 usedChannels;
		std::map<std::string, int> *channels; //path, channel
		std::array<Mix_Chunk*, MAX_CHANNELS> *sounds;

	public:
		SoundPlayer();
		~SoundPlayer();

		void play(std::string path, bool loop);
		void stop();
		void stopByFile(std::string path);
		void loadFromFile(std::string path);
		void removeSoundByFile(std::string path);
};