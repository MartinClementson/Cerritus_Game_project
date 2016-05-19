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
	//timeElapsed = 0;
	AUDIO_ENGINE_FLAGS eflags = AudioEngine_Default;
#ifdef _DEBUG
	eflags = (eflags | AudioEngine_Debug);
#endif
	//assigning the audio engine
	s_audEngine = new std::unique_ptr<AudioEngine>(new AudioEngine(eflags));

	//loading the shoot sound
	//prefix to the soundfolder is "sounds/"
	s_shot.reset(new SoundEffect(s_audEngine->get(), L"sounds/shot.wav"));
	s_ambient.reset(new SoundEffect(s_audEngine->get(), L"sounds/NightAmbienceSimple_02.wav"));
	s_E_death.reset(new SoundEffect(s_audEngine->get(), L"sounds/E_death2.wav"));
	s_gameTheme.reset(new SoundEffect(s_audEngine->get(), L"sounds/test_teme.wav"));
	s_healthPickup.reset(new SoundEffect(s_audEngine->get(), L"sounds/health_pickup.wav"));
	s_weaponPickup.reset(new SoundEffect(s_audEngine->get(), L"sounds/shot_pickup.wav"));
	s_imminentWave.reset(new SoundEffect(s_audEngine->get(), L"sounds/new_wave.wav"));
	s_loseAmient.reset(new SoundEffect(s_audEngine->get(), L"sounds/lose.wav"));

	s_nightLoop = s_ambient->CreateInstance();
	s_musicLoop = s_gameTheme->CreateInstance();
	s_loseLoop = s_loseAmient->CreateInstance();

	s_nightLoop->Play(true);
	s_nightLoop->SetVolume(0.3f);
	s_musicLoop->Play(true);
	s_musicLoop->SetVolume(0.5f);
	s_loseLoop->SetVolume(0.5f);

	s_audEngine->get()->SetMasterVolume(0.1f);
}

void AudioManager::Update(double deltaTime)
{
	if (s_retryAudio)
	{
		s_retryAudio = false;
		s_audEngine->get()->Reset();
		s_nightLoop->Play(true);
		s_musicLoop->Play(true);
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
	s_shot->Play(0.4f, 0,0);
}

void AudioManager::playEDeathSound()
{
	s_E_death->Play();
}

void AudioManager::playHealthPickup()
{
	s_healthPickup->Play();
}

void AudioManager::playWeaponPickup()
{
	s_weaponPickup->Play();
}

void AudioManager::playNewWave()
{
	s_imminentWave->Play(1.5f,0,0);
}

void AudioManager::playInGameLoop()
{
	s_musicLoop->Play(true);
	s_nightLoop->Play(true);
}

void AudioManager::stopAmbientGameStateSound()
{
	s_nightLoop->Pause();
	s_musicLoop->Pause();
}
