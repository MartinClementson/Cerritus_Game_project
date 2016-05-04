#pragma once
#include "../LibIncluder.h"
class GameTimer
{
public:
	
	
	static GameTimer* GetInstance();

	double GameTime()const; //in seconds
	double DeltaTime()const; //in seconds
	double TotalTime() const; // A timer, can be used for in game timers, level time/ bomb explosion time, animation time. anything 

	void Reset(); //call before message loop
	void Start(); // call when unpaused
	void Stop(); // Call when paused
	void Tick(); //call every frame

	 ~GameTimer();
private:
	GameTimer();
	double mSecondsPerCount;
	double mDeltaTime;

	__int64 mBaseTime;
	__int64 mPausedTime;
	__int64 mStopTime;
	__int64 mPrevTime;
	__int64 mCurrTime;

	bool mStopped;
};

