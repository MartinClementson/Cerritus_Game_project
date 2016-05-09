#include "AudioManager.h"



AudioManager::AudioManager()
{
}


AudioManager::~AudioManager()
{
	if (audEngine != nullptr)
		delete audEngine;
}

void AudioManager::Release()
{
	//add things later
}

void AudioManager::Initialize()
{
	AUDIO_ENGINE_FLAGS eflags = AudioEngine_Default;
#ifdef _DEBUG
	eflags = (eflags | AudioEngine_Debug);
#endif
	audEngine = new std::unique_ptr<AudioEngine>(new AudioEngine(eflags));
	//audEngine->get()->Update();
}
