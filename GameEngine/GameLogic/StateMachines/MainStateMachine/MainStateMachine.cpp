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
	
	if (this->activeState == MAIN_GAME_STATE && gameState->isPlayerDead == true)
	{
		gameState->isActive = false;

		if (gameOverState)
		{
			gameOverState->Release();
			delete gameOverState;
		}

		this->gameOverState = new GameOverState();
		gameOverState->Initialize();
		gameOverState->isActive = true;
		
		this->activeState = MAIN_GAMEOVER_STATE;

	}
	if (this->activeState == MAIN_GAMEOVER_STATE && gameOverState->replay == true)
	{
		gameOverState->isActive = false;
		

		if (gameState)
		{
			gameState->Release();
			delete gameState;
		}

		this->gameState = new GameState();
		gameState->Initialize();
		gameState->isActive = true;
		
		this->activeState = MAIN_GAME_STATE;
	}
	//key esc pressed menu
	
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
	this->gameOverState->isActive = false;
	this->menuState->isActive = false;
	this->delay = 0.0f;
}

void MainStateMachine::Release()
{

}
