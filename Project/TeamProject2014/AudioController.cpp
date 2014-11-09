#include "AudioController.hpp"


AudioController::AudioController()
{
}

AudioController::~AudioController()
{
	Mix_Quit();
}

void AudioController::playMusic(const char* path, bool loop)
{
	if (musicPlayer.isMusicPlaying())
		stopMusic();

	musicPlayer.loadFromFile(path);
	musicPlayer.play(loop);
}

void AudioController::stopMusic()
{
	musicPlayer.stop();
}

void AudioController::addSound(const char* path)
{
	soundPlayer.loadFromFile(path);
}

void AudioController::removeSound(const char* path)
{
	soundPlayer.removeSoundByFile(path);
}

void AudioController::playSound()
{
	soundPlayer.play(true);
}

void AudioController::stopSound()
{
	soundPlayer.stop();
}

void AudioController::stopAudio()
{
	stopMusic();
	stopSound();
}