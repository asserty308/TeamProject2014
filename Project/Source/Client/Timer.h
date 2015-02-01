#pragma once
#include "singleton.hpp"

#define g_pTimer Timer::Get()

class Timer :
	public Singleton<Timer>
{
public:
	Timer(void);
	
	void init();
	void update();

	float getDeltaTime();

private:
	float currentTime;
	float lastTime;
	float deltaTime;

};

