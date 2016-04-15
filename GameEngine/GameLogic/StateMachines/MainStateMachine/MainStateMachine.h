#pragma once
#include "./GameState/GameState.h"
#include "./GameOverState/GameOverState.h"
#include "./MenuState/MenuState.h"
#include "../../../Enumerations/Enumerations.h"
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

