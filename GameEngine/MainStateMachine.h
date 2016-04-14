#pragma once
#include "GameState.h"
#include "GameOverState.h"
#include "MenuState.h"
class MainStateMachine
{
public:
	MainStateMachine();
	~MainStateMachine();
	void Update(double deltaTime);
	void Render();
	void Initialize();
	void Release();
private:
	GameState* gameState;
	GameOverState* gameOverState;
	MenuState* menuState;
	//States activeState;//enum

};

