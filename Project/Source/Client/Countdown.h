#include "Timer.h"

#define ONESECOND 1.0f

enum CountdownState{INITIALIZED, RUNNING, FINISHED, PAUSED};

class Countdown{
public:
	Countdown(int startCount);
	~Countdown();

	void start();
	void stop();
	void reset();
	void run();

	CountdownState getState(){ return state; }

	int getCurrentCountdown(){ return countdown; }
	void setCountdown(int countdown){ this->startCount = countdown; }

private:
	int startCount;
	int countdown;

	CountdownState state;
	
	float deltaTime;



};