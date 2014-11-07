#include "AudioController.hpp"


AudioController::AudioController()
{
}

AudioController::~AudioController()
{
}

void AudioController::playMusic()
{
	musicPlayer.loadFromFile("Audio/Music/space2a.wav");
	musicPlayer.play(true);
}