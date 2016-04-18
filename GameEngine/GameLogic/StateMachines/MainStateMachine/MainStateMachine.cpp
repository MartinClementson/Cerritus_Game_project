#include "MainStateMachine.h"



MainStateMachine::MainStateMachine()
{
	this->gameState = new GameState();
	this->gameOverState = new GameOverState();
	this->menuState = new MenuState();
}


MainStateMachine::~MainStateMachine()
{
	delete this->gameState;
	delete this->gameOverState;
	delete this->menuState;
}

void MainStateMachine::Update(double deltaTime)
{
	if (gameState->isActive)
	{
		gameState->Update(deltaTime);
	}
	else if (gameOverState->isActive)
	{
		gameOverState->Update(deltaTime);
	}
	else if (menuState->isActive)
	{
		menuState->Update(deltaTime);
	}
}

void MainStateMachine::Render()
{
	if(gameState->isActive)
	{
		gameState->Render();
	}
	else if (gameOverState->isActive)
	{
		gameOverState->Render();
	}
	else if (menuState->isActive)
	{
		menuState->Render();
	}
}

void MainStateMachine::Initialize()
{
	gameState->Initialize();
	this->activeState = MAIN_GAME_STATE;
	this->gameState->isActive = true;
}

void MainStateMachine::Release()
{
}
