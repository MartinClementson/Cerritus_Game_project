#include "AudioManager.h"
//#define AUDIO_FOLDER "../../../sounds/"

AudioManager::AudioManager()
{
}


AudioManager::~AudioManager()
{
	if (s_audEngine != nullptr)
	{
		delete s_audEngine;
		//delete s_shot;
	}
}

void AudioManager::Release()
{
	//s_shot.release();
	//add things later
}

void AudioManager::Initialize()
{
	timeElapsed = 0;
	AUDIO_ENGINE_FLAGS eflags = AudioEngine_Default;
#ifdef _DEBUG
	eflags = (eflags | AudioEngine_Debug);
#endif
	//assigning the audio engine
	s_audEngine = new std::unique_ptr<AudioEngine>(new AudioEngine(eflags));

	//loading the shoot sound
	//prefix to the soundfolder is "sounds/"
	s_shot.reset(new SoundEffect(s_audEngine->get(), L"sounds/shot4.wav"));
	s_ambient.reset(new SoundEffect(s_audEngine->get(), L"sounds/NightAmbienceSimple_02.wav"));
	//audioLength = s_shot->GetSampleDurationMS() / 1000.0;
	s_nightLoop = s_ambient->CreateInstance();
	s_nightLoop->Play(true);
	s_nightLoop->SetVolume(0.1);
}

void AudioManager::Update(double deltaTime)
{
	//code for looping a audiofile
	/*timeElapsed += deltaTime;
	if (timeElapsed >= audioLength)
	{
		s_shot->Play();
		timeElapsed = 0;
	}*/

	if (s_retryAudio)
	{
		s_retryAudio = false;
		s_audEngine->get()->Reset();
		s_nightLoop->Play(true);
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

void AudioManager::playShotSound()
{
	s_shot->Play();
}
