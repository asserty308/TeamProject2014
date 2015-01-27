#pragma once
#include <SDL_mixer.h>
#include <string>

class MusicPlayer
{
	private:
		Mix_Music *musicFile;

	public:
		MusicPlayer();
		~MusicPlayer();

		void loadFromFile(std::string path);
		void play(bool loop);
		void stop();
		bool isMusicPlaying();
};

