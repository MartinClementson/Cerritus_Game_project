#pragma once
#include "../Audio/SoundCommon.h"
#include "../Audio/WAVFileReader.h"
#include "../../../Source/LibIncluder.h"
#include <Audio.h>
using namespace DirectX;
class AudioManager
{
private:
	//std::shared_ptr<AudioEngine> audEngine;
public:
	AudioManager();
	~AudioManager();
	void Release();
	void Initialize();
};

