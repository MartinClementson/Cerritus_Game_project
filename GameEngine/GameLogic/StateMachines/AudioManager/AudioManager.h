#pragma once
#include "../Audio/SoundCommon.h"
#include "../Audio/WAVFileReader.h"
#include "../../../Source/LibIncluder.h"
#include <Audio.h>
#include "../GameTimer/GameTimer.h"
using namespace DirectX;
class AudioManager
{
private:
	std::unique_ptr<AudioEngine>* s_audEngine = nullptr;

	std::unique_ptr<SoundEffect> s_shot;
	bool s_retryAudio = false;
	double timeElapsed;
	double audioLength;
public:
	AudioManager();
	~AudioManager();
	void Release();
	void Initialize();
	void Update(double deltaTime);

	//functions for playing the sounds
	void playShotSound();
};

