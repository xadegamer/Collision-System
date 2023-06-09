
#include "TimeManager.h"

TimeManager::TimeManager()
{
	//Initialize the variables
	mStartTicks = 0;
	mPausedTicks = 0;

	now = SDL_GetPerformanceCounter();
	last = 0;

	mPaused = false;
	mStarted = false;
}

void TimeManager::tick()
{
	//Start the timer
	mStarted = true;

	//Unpause the timer
	mPaused = false;

	//Get the current clock time
	mStartTicks = SDL_GetTicks();
	mPausedTicks = 0;

	calDeltaTime();
}

void TimeManager::stop()
{
	//Stop the timer
	mStarted = false;

	//Unpause the timer
	mPaused = false;

	//Clear tick variables
	mStartTicks = 0;
	mPausedTicks = 0;
}

void TimeManager::pause()
{
	//If the timer is running and isn't already paused
	if (mStarted && !mPaused)
	{
		//Pause the timer
		mPaused = true;

		//Calculate the paused ticks
		mPausedTicks = SDL_GetTicks() - mStartTicks;
		mStartTicks = 0;
	}
}

void TimeManager::unpause()
{
	//If the timer is running and paused
	if (mStarted && mPaused)
	{
		//Unpause the timer
		mPaused = false;

		//Reset the starting ticks
		mStartTicks = SDL_GetTicks() - mPausedTicks;

		//Reset the paused ticks
		mPausedTicks = 0;

		calDeltaTime();
	}
}

void TimeManager::reset()
{
	mStartTicks = 0;
}

Uint32 TimeManager::getTicks()
{
	//The actual timer time
	Uint32 time = 0;

	//If the timer is running
	if (mStarted)
	{
		//If the timer is paused
		if (mPaused)
		{
			//Return the number of ticks when the timer was paused
			time = mPausedTicks;
		}
		else
		{
			//Return the current time minus the start time
			time = SDL_GetTicks() - mStartTicks;
		}
	}

	return time;
}

void TimeManager::calDeltaTime()
{
	last = now;
	now = SDL_GetPerformanceCounter();
}

double TimeManager::getDeltaTime()
{
	return  ((now - last) / (double)SDL_GetPerformanceFrequency());
}

double TimeManager::getCurrentTime()
{
	return getTicks() / 1000.0f;
}

bool TimeManager::isStarted()
{
	//Timer is running and paused or unpaused
	return mStarted;
}

bool TimeManager::isPaused()
{
	//Timer is running and paused
	return mPaused && mStarted;
}