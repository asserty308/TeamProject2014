#include "Countdown.h"
#include "Logger.hpp"

Countdown::Countdown(int startCount){
	countdown = startCount;
	this->startCount = startCount;
	deltaTime = 0.0f;
	state = INITIALIZED;
}

Countdown::~Countdown(){

}

void Countdown::start(){
	state = RUNNING;
}

void Countdown::stop(){
	state = PAUSED;
}

void Countdown::reset(){
	countdown = startCount;
	deltaTime = 0.0f;
	state = INITIALIZED;
}

void Countdown::run(){
	switch (state){
	case(INITIALIZED) :
		break;
	case(RUNNING) :
		deltaTime += g_pTimer->getDeltaTime();
		if (deltaTime > ONESECOND){
			countdown--;
			deltaTime = 0.0f;
		}

		if (countdown <= 0){
			state = FINISHED;
			countdown = startCount;
			deltaTime = 0.0f;
		}
		break;
	case(FINISHED) :
		break;
	case(PAUSED) :
		break;
	}
}