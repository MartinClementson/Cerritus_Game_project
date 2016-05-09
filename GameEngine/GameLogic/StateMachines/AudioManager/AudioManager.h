#pragma once
#include "../Audio/SoundCommon.h"
#include "../Audio/WAVFileReader.h"
#include "../../../Source/LibIncluder.h"
#include <Audio.h>
using namespace DirectX;
class AudioManager
{
private:
	std::unique_ptr<AudioEngine>* s_audEngine = nullptr;

	std::unique_ptr<SoundEffect> s_shot;
	bool s_retryAudio = false;

public:
	AudioManager();
	~AudioManager();
	void Release();
	void Initialize();
	void Update();
};

