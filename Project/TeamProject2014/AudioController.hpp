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

		//float masterVolume;

	public:
		AudioController();
		~AudioController();

		void playMusic();
		//void playSound();

		void stopMusic();
		/*void stopSound();
		void stopAudio();*/
};

