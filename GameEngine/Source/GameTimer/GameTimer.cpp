#include "GameTimer.h"
#include "../LibIncluder.h"



GameTimer::GameTimer()
	:mSecondsPerCount(0.0), mDeltaTime(-1.0), mBaseTime(0), mPausedTime(0),
	mPrevTime(0), mCurrTime(0), mStopped(false)
{
	//Query the frequency of the performance counter

	__int64 countsPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);

	mSecondsPerCount = 1.0 / (double)countsPerSec;
}

GameTimer * GameTimer::GetInstance()
{
	static GameTimer instance;

	return &instance;
}

double GameTimer::GameTime() const
{
	return 0.0;
}

double GameTimer::DeltaTime() const
{
	return (double)mDeltaTime;
}

double GameTimer::TotalTime() const
{
	// If we are stopped, do not count the time that has passed since we stopped.
	// Moreover, if we previously already had a pause, the distance 
	// mStopTime - mBaseTime includes paused time, which we do not want to count.
	// To correct this, we can subtract the paused time from mStopTime:  
	//
	//                     |<--paused time-->|
	// ----*---------------*-----------------*------------*------------*------> time
	//  mBaseTime       mStopTime        startTime     mStopTime    mCurrTime

	if (mStopped)
	{
		return (double)(((mStopTime - mPausedTime) - mBaseTime)*mSecondsPerCount);
	}

	// The distance mCurrTime - mBaseTime includes paused time,
	// which we do not want to count.  To correct this, we can subtract 
	// the paused time from mCurrTime:  
	//
	//  (mCurrTime - mPausedTime) - mBaseTime 
	//
	//                     |<--paused time-->|
	// ----*---------------*-----------------*------------*------> time
	//  mBaseTime       mStopTime        startTime     mCurrTime

	else
	{
		return (double)(((mCurrTime - mPausedTime) - mBaseTime)*mSecondsPerCount);
	}
}

void GameTimer::Reset()
{
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

	mBaseTime = currTime;
	mPrevTime = currTime;
	mStopTime = 0;
	mStopped = false;
}

void GameTimer::Start()
{
	__int64 startTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&startTime);


	// Accumulate the time elapsed between stop and start pairs.
	//
	//                     |<-------d------->|
	// ----*---------------*-----------------*------------> time
	//  mBaseTime       mStopTime        startTime     

	if (mStopped)
	{
		mPausedTime += (startTime - mStopTime);

		mPrevTime = startTime;
		mStopTime = 0;
		mStopped = false;
	}
}

void GameTimer::Stop()
{
	if (!mStopped)
	{
		__int64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

		mStopTime = currTime;
		mStopped = true;
	}
}

void GameTimer::Tick()
{
	if (mStopped)
	{
		mDeltaTime = 0.0;
		return;
	}

	//Get the time of this frame
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	this->mCurrTime = currTime;

	//time difference between this frame and the previous
	mDeltaTime = (mCurrTime - mPrevTime)* mSecondsPerCount;


	//prepare for next frame

	mPrevTime = mCurrTime;

	//force non negative
	//if the processor goes into power save mode, this can be negative
	//we dont want that David.

	if (mDeltaTime < 0.0)
		mDeltaTime = 0.0;


}


GameTimer::~GameTimer()
{
}
