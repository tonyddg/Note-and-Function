#pragma once
#include<ctime>

class HighAccTimer
{

};

class timer
{
public:

	timer();

	bool Clean();
	bool GetIsRunning();
	bool Start();
	bool Stop();
	void Reset();
	clock_t Read();

	clock_t SleepTill(clock_t ctSleepTime);

private:

	clock_t ctStartTime;
	clock_t ctStopgapTime;

	bool blIsRunning;

};

class FPSCounter
{
public:

	FPSCounter(clock_t iFlushRateG);

	void Init();
	void Count();
	double Read();

private:

	timer tmTimeControler;
	int iCounter;
	double dbFPS;

	clock_t ctFlushRate;
};

void HighAccSleep(long ms);