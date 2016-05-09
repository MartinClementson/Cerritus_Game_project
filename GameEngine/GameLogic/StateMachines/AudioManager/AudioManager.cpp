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

void AudioManager::Update()
{
	if (m_retryAudio)
	{
		m_retryAudio = false;
		audEngine->reset();
		//if there are any looped sounds, reset them here
	}

	else if (!audEngine->get()->Update())
	{
		//if this loop is entered, no audio device is detected
		//trying to reset it.
		if (audEngine->get()->IsCriticalError())
		{
			m_retryAudio = true;
		}
	}
}
