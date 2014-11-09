#pragma once
#include <SDL_mixer.h>
#include "Singleton.hpp"
#include "MusicPlayer.hpp"
#include "SoundPlayer.hpp"

#define g_pAudioController AudioController::Get()

class AudioController : public Singleton<AudioController>
{
	private:
		MusicPlayer musicPlayer;
		SoundPlayer soundPlayer;

		float masterVolume;

	public:
		AudioController();
		~AudioController();

		//music related functions
		void playMusic(const char* path, bool loop);
		void stopMusic();

		//sound related functions
		void addSound(const char* path);
		void removeSound(const char* path);
		void playSound();
		void stopSound();

		void stopAudio();
};

