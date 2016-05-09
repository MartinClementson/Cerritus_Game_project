#pragma once
#include "../Audio/SoundCommon.h"
#include "../Audio/WAVFileReader.h"
#include "../../../Source/LibIncluder.h"
#include <Audio.h>
using namespace DirectX;
class AudioManager
{
private:
	std::unique_ptr<AudioEngine>* audEngine = nullptr;
public:
	AudioManager();
	~AudioManager();
	void Release();
	void Initialize();
};

