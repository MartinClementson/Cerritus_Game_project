#pragma once
class GameTimer
{
public:
	GameTimer();
	



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

