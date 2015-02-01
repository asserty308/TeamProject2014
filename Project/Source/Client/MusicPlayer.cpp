#include "MusicPlayer.hpp"
#include "Logger.hpp"

MusicPlayer::MusicPlayer()
{
	//Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		g_pLogfile->fLog("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());

	musicFile = nullptr;
}

MusicPlayer::~MusicPlayer()
{
	Mix_FreeMusic(musicFile);
	musicFile = nullptr;
}

void MusicPlayer::loadFromFile(std::string path)
{
	musicFile = Mix_LoadMUS(path.c_str());

	if (musicFile == nullptr)
		g_pLogfile->fLog("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
}

void MusicPlayer::play(bool loop)
{
	int loops;

	//-1 = loop infinite times
	loop ? loops = -1 : loops = 0;
	
	Mix_PlayMusic(musicFile, loops);
}

void MusicPlayer::stop()
{
	if (isMusicPlaying())
		Mix_HaltMusic();
}

bool MusicPlayer::isMusicPlaying()
{
	//true when music is playing
	return Mix_PlayingMusic() != 0;
}