#include "AudioController.hpp"


AudioController::AudioController()
{
	musicPlayer = new MusicPlayer();
	soundPlayer = new SoundPlayer();
}

AudioController::~AudioController()
{
	delete musicPlayer;
	delete soundPlayer;

	Mix_Quit();
}

void AudioController::playMusic(std::string path, bool loop)
{
	if (musicPlayer->isMusicPlaying())
		stopMusic();

	musicPlayer->loadFromFile(path);
	musicPlayer->play(loop);
}

void AudioController::stopMusic()
{
	musicPlayer->stop();
}

void AudioController::addSound(std::string path)
{
	soundPlayer->loadFromFile(path);
}

void AudioController::removeSound(std::string path)
{
	soundPlayer->removeSoundByFile(path);
}

void AudioController::playSound(std::string path, bool loop)
{
	soundPlayer->play(path, true);
}

void AudioController::stopSoundByFile(std::string path)
{
	soundPlayer->stopByFile(path);
}

void AudioController::stopAudio()
{
	stopMusic();
	soundPlayer->stop();
}