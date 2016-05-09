#include "AudioManager.h"
//#define AUDIO_FOLDER "../../../sounds/"

AudioManager::AudioManager()
{
}


AudioManager::~AudioManager()
{
	if (s_audEngine != nullptr)
		delete s_audEngine;
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
	//assigning the audio engine
	s_audEngine = new std::unique_ptr<AudioEngine>(new AudioEngine(eflags));

	//loading the shoot sound
	//prefix to the soundfolder is "../../../sounds/"
	s_shot.reset(new SoundEffect(s_audEngine->get(), L"sounds/Explo1.wav" ));
}

void AudioManager::Update()
{
	if (s_retryAudio)
	{
		s_retryAudio = false;
		s_audEngine->reset();
		//if there are any looped sounds, reset them here
	}

	else if (!s_audEngine->get()->Update())
	{
		//if this loop is entered, no audio device is detected
		//trying to reset it.
		if (s_audEngine->get()->IsCriticalError())
		{
			s_retryAudio = true;
		}
	}
}
