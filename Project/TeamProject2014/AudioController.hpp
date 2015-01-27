#pragma once
#include <SDL_mixer.h>
#include <string>
#include "Singleton.hpp"
#include "MusicPlayer.hpp"
#include "SoundPlayer.hpp"

#define g_pAudioController AudioController::Get()

class AudioController : public Singleton<AudioController>
{
	private:
		MusicPlayer *musicPlayer;
		SoundPlayer *soundPlayer;

		float masterVolume;

	public:
		AudioController();
		~AudioController();

		//music related functions
		void playMusic(std::string path, bool loop);
		void stopMusic();

		//sound related functions
		void addSound(std::string path);
		void removeSound(std::string path);
		void playSound(std::string path, bool loop);
		void stopSoundByFile(std::string path);

		void stopAudio();
};

