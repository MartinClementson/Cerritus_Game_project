#pragma once
#include "./GameState/GameState.h"
#include "./GameOverState/GameOverState.h"
#include "./MenuState/MenuState.h"
#include "../../../Enumerations/Enumerations.h"
#include "../AudioManager/AudioManager.h"
class MainStateMachine
{
public:
	MainStateMachine();
	virtual ~MainStateMachine();
	void Update(double deltaTime);
	void Render();
	void Initialize();
	float delay;
	float lastHighscore;
	void Release();
	
private:

	AudioManager* audioManager = nullptr;
	GameState* gameState;
	GameOverState* gameOverState;
	MenuState* menuState;
	MainStates activeState;//enum
	

};

