#include "SoundPlayer.hpp"
#include "Logger.hpp"

SoundPlayer::SoundPlayer()
{
	maxChannels = 20;
	usedChannels = 0;
}


SoundPlayer::~SoundPlayer()
{
}

void SoundPlayer::loadFromFile(const char* path)
{
	if (usedChannels < maxChannels)
	{
		Mix_Chunk *soundFile = Mix_LoadWAV(path);

		if (soundFile == nullptr)
			g_pLogfile->fLog("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		else
		{
			auto it = sounds.find(path);

			//only add when it has not already been added
			if (it == sounds.end())
			{
				sounds[path] = soundFile;
				usedChannels++;
			}
		}
	}
}

void SoundPlayer::removeSoundByFile(const char* path)
{
	auto it = sounds.find(path);

	//if file is found
	if (it != sounds.end())
	{
		auto cmpIT = sounds.begin();
		for (int i = 0; i < sounds.size(); i++)
		{
			/*compare the length (bytes) of each file
			  and stop the channel*/
			if (it->second->alen == cmpIT->second->alen)
			{
				Mix_HaltChannel(i);
				usedChannels--;
				break;
			}

			++cmpIT;
		}

		sounds.erase(it);
	}
}

void SoundPlayer::play(bool loop)
{
	auto it = sounds.begin();
	for (int i = 0; i < sounds.size(); i++)
	{
		if (!Mix_Playing(i))
		{
			Mix_PlayChannel(i, it->second, -1);
		}

		it++;
	}
}

void SoundPlayer::stop()
{
	for (int i = 0; i < sounds.size(); i++)
		Mix_HaltChannel(i);
}