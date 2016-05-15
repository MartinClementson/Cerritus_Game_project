#include "MainStateMachine.h"

MainStateMachine::MainStateMachine()
{
	this->gameState = new GameState();
	this->gameOverState = new GameOverState();
	this->menuState = new MenuState();
	this->audioManager = new AudioManager();
}


MainStateMachine::~MainStateMachine()
{
	delete this->gameState;
	delete this->gameOverState;
	delete this->menuState;
	delete this->audioManager;
}

void MainStateMachine::Update(double deltaTime)
{
	audioManager->Update(deltaTime);
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
		gameOverState->SetLastHigh(lastHighscore);
		gameOverState->SetPoints(gameState->GetPoints());
		if (lastHighscore < gameState->GetPoints())
		{
			lastHighscore = gameState->GetPoints();
		}
		
		this->activeState = MAIN_GAMEOVER_STATE;

	}
	if (this->activeState == MAIN_GAME_STATE && gameState->toMenu == true)
	{
		gameState->isActive = false;
		if (menuState)
		{
			menuState->Release();
			delete menuState;
		}
		this->menuState = new MenuState();
		menuState->Initialize();
		menuState->isActive = true;

		this->activeState = MAIN_MENU_STATE;
		//gameState->toMenu = false;
		
	}
	if (this->activeState == MAIN_MENU_STATE && menuState->exitMenu == true)
	{
		menuState->isActive = false;

		if (gameState)
		{
			gameState->Release();
			delete gameState;
		}
		this->gameState = new GameState();
		gameState->Initialize(audioManager);
		gameState->isActive = true;

		this->activeState = MAIN_GAME_STATE;
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
		gameState->Initialize(audioManager);
		gameState->isActive = true;
		
		this->activeState = MAIN_GAME_STATE;
	}
	else if (this->activeState == MAIN_GAMEOVER_STATE && gameOverState->toMenu == true)
	{
		gameOverState->isActive = false;


		if (menuState)
		{
			menuState->Release();
			delete menuState;
		}

		this->menuState = new MenuState();
		menuState->Initialize();
		menuState->isActive = true;

		this->activeState = MAIN_MENU_STATE;
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
	audioManager->Initialize();
	gameState->Initialize(audioManager);
	this->activeState = MAIN_GAME_STATE;
	this->gameState->isActive = true;
	this->gameOverState->isActive = false;
	this->menuState->isActive = false;
	this->delay = 0.0f;
	this->lastHighscore = 0.0f;
	gameState->toMenu = true;
}

void MainStateMachine::Release()
{
	audioManager->Release();
}
