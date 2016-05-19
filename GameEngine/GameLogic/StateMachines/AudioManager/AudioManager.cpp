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
	s_repair.reset(new SoundEffect(s_audEngine->get(), L"sounds/repair.wav"));
	s_repair_complete.reset(new SoundEffect(s_audEngine->get(), L"sounds/repair_complete.wav"));
	s_player_Hit.reset(new SoundEffect(s_audEngine->get(), L"sounds/Player_hit.wav"));
	s_enemy_Hit.reset(new SoundEffect(s_audEngine->get(), L"sounds/emeny_hit2.wav"));

	s_repairLoop = s_repair->CreateInstance();
	s_nightLoop = s_ambient->CreateInstance();
	s_musicLoop = s_gameTheme->CreateInstance();
	s_loseLoop = s_loseAmient->CreateInstance();

	//s_nightLoop->Play(true);
	s_nightLoop->SetVolume(0.3f);
	//s_musicLoop->Play(true);
	s_musicLoop->SetVolume(0.5f);
	s_loseLoop->SetVolume(0.6f);
	s_repairLoop->Play(true);
	s_repairLoop->Pause();
	s_repairLoop->SetVolume(1.2f);

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
	s_shot->Play(0.5f, 0,0);
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

void AudioManager::playRepairComplete()
{
	s_repair_complete->Play(0.7f,0,0);
}

void AudioManager::playPlayerHit()
{
	s_player_Hit->Play();
}

void AudioManager::playEnemyHit()
{
	s_enemy_Hit->Play();
}

void AudioManager::playInGameLoop()
{
	s_musicLoop->Play(true);
	s_nightLoop->Play(true);
}

void AudioManager::playLoseLoop()
{
	s_loseLoop->Play(true);
}

void AudioManager::playRepairLoop()
{
	s_repairLoop->Resume();
}

void AudioManager::stopRepairLoop()
{
	s_repairLoop->Pause();
}

void AudioManager::stopLoseLoop()
{
	s_loseLoop->Pause();
}

void AudioManager::stopAmbientGameStateSound()
{
	s_nightLoop->Pause();
	s_musicLoop->Pause();
}

AudioManager* AudioManager::GetInstance()
{
	static AudioManager instance;
	return &instance;
}
