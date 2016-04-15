#pragma once
#include "GameState.h"
#include "GameOverState.h"
#include "MenuState.h"
#include "Enumerations.h"
class MainStateMachine
{
public:
	MainStateMachine();
	virtual ~MainStateMachine();
	void Update(double deltaTime);
	void Render();
	void Initialize();
	void Release();
private:
	GameState* gameState;
	GameOverState* gameOverState;
	MenuState* menuState;
	MainStates activeState;//enum

};

