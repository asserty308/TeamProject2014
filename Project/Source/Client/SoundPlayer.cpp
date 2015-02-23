#include "SoundPlayer.hpp"
#include "Logger.hpp"
#include "AudioFiles.hpp"

SoundPlayer::SoundPlayer()
{
	usedChannels = 0;

	channels = new std::map<std::string, int>();
	sounds = new std::array<Mix_Chunk*, MAX_CHANNELS>();

	loadFromFile(SoundFiles::ROCKET);
	loadFromFile(SoundFiles::EXPLOSION);
	loadFromFile(SoundFiles::BOOST);
}


SoundPlayer::~SoundPlayer()
{
	delete channels;
	delete sounds;
}

void SoundPlayer::loadFromFile(std::string path)
{
	if (usedChannels < MAX_CHANNELS)
	{
		Mix_Chunk *soundFile = Mix_LoadWAV(path.c_str());

		if (soundFile == nullptr)
		{
			g_pLogfile->fLog("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		}
		else
		{
			auto it = channels->find(path);

			//only add when it has not already been added
			if (it == channels->end())
			{
				channels->insert(std::make_pair(path, usedChannels));
				sounds->at(usedChannels) = soundFile;
				usedChannels++;
			}
		}
	}
}

void SoundPlayer::removeSoundByFile(std::string path)
{
	auto it = channels->find(path);

	//if file is found
	if (it != channels->end())
	{
		Mix_HaltChannel(channels->at(path));

		sounds->at(channels->at(path)) = nullptr;
		channels->erase(it);

		usedChannels--;
	}
}

void SoundPlayer::play(std::string path, bool loop)
{
	auto it = channels->find(path);
	int loops = loop ? -1 : 0; //-1 = infinite, 0 = no loop

	if (it != channels->end())
	{
		int ch = channels->at(path);

		if (!Mix_Playing(ch))
		{
			Mix_PlayChannel(ch, sounds->at(ch), loops);
		}
	}
}

void SoundPlayer::stop()
{
	for (int i = 0; i < channels->size(); i++)
		Mix_HaltChannel(i);
}

void SoundPlayer::stopByFile(std::string path)
{
	auto it = channels->find(path);

	if (it != channels->end())
	{
		Mix_HaltChannel(channels->at(path));
	}
}