#include"timersup.h"
#include<Windows.h>

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

timer::timer()
{
	ctStartTime = 0;
	ctStopgapTime = -1;

	blIsRunning = false;
}

bool timer::Clean()
{
	if (blIsRunning)
	{
		ctStopgapTime = -1;
		ctStartTime = clock();

		return true;
	}
	else
	{
		return false;
	}
}

bool timer::Start()
{
	if (blIsRunning)
	{
		return false;
	}
	else
	{
		if(ctStopgapTime != -1)ctStartTime = clock() - ctStartTime + ctStopgapTime;
		else ctStartTime = clock();

		blIsRunning = true;

		return true;
	}

}

bool timer::Stop()
{
	if (blIsRunning)
	{
		ctStopgapTime = clock();
		blIsRunning = false;

		return true;
	}
	else
	{
		return false;
	}
}

clock_t timer::Read()
{
	if (blIsRunning)
	{
		return clock() - ctStartTime;
	}
	else
	{
		return ctStartTime - ctStopgapTime;
	}
}

void timer::Reset()
{
	ctStartTime = 0;
	ctStopgapTime = -1;

	blIsRunning = false;
}

//确保timer为开启状态，否则返回-1 一般情况返回时差
clock_t timer::SleepTill(clock_t ctSleepTime)
{
	if (blIsRunning)
	{
		while (Read() - ctSleepTime < 0)//直接使用Sleep将有延迟
		{
			Sleep(0);
		}

		clock_t ctGapTime = Read() - ctSleepTime;

		Clean();

		return ctGapTime;
	}
	else return -1;
}

bool timer::GetIsRunning()
{
	return blIsRunning;
}

FPSCounter::FPSCounter(clock_t ctFlushRateG)
{
	iCounter = 0;
	dbFPS = 0.0;

	ctFlushRate = ctFlushRateG;
}

void FPSCounter::Init()
{
	tmTimeControler.Start();
}

void FPSCounter::Count()
{
	clock_t ctCurrentTime = tmTimeControler.Read();

	if (ctCurrentTime < ctFlushRate)
	{
		iCounter++;
	}
	else
	{
		dbFPS = (double)iCounter / ((double)ctCurrentTime / 1000.0);

		iCounter = 1;

		tmTimeControler.Clean();
	}
}

double FPSCounter::Read()
{
	return dbFPS;
}

void HighAccSleep(long ms)
{
	TIMECAPS tc;
	timeGetDevCaps(&tc, sizeof(TIMECAPS));
	timeBeginPeriod(tc.wPeriodMin);
	::Sleep(ms);
	timeEndPeriod(tc.wPeriodMin);
}
