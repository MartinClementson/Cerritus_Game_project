#include "AudioManager.h"



AudioManager::AudioManager()
{
}


AudioManager::~AudioManager()
{
}

void AudioManager::Release()
{
}

void AudioManager::Initialize()
{
	AUDIO_ENGINE_FLAGS eflags = AudioEngine_Default;
#ifdef _DEBUG
	eflags = eflags | AudioEngine_Debug;
#endif
	std::unique_ptr<AudioEngine> audEngine(new AudioEngine(eflags));
}
