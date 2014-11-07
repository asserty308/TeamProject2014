#pragma once

class AudioBase
{
	public:
		virtual void play(bool loop) = 0;
		virtual void stop() = 0;
		virtual void loadFromFile(const char* path) = 0;
};