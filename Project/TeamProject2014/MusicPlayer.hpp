#pragma once
#include <SDL_mixer.h>
#include "AudioBase.hpp"

class MusicPlayer : public AudioBase
{
	private:
		Mix_Music *musicFile;

	public:
		MusicPlayer();
		~MusicPlayer();

		void loadFromFile(const char* path);
		void play(bool loop);
		void stop();
		bool isMusicPlaying();
};

