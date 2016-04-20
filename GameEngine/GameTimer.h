#pragma once
#include "Source\LibIncluder.h"
class GameTimer
{
public:
	GameTimer();
	


	float GameTime()const; //in seconds
	float DeltaTime()const; //in seconds
	float TotalTime() const; // A timer, can be used for in game timers, level time/ bomb explosion time, animation time. anything 

	void Reset(); //call before message loop
	void Start(); // call when unpaused
	void Stop(); // Call when paused
	void Tick(); //call every frame

	 ~GameTimer();
private:
	double mSecondsPerCount;
	double mDeltaTime;

	__int64 mBaseTime;
	__int64 mPausedTime;
	__int64 mStopTime;
	__int64 mPrevTime;
	__int64 mCurrTime;

	bool mStopped;
};

