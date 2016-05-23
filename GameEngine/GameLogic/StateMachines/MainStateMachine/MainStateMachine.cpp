#include "MainStateMachine.h"

MainStateMachine::MainStateMachine()
{
	this->gameState = new GameState();
	this->gameOverState = new GameOverState();
	this->winState = new WinState();
	this->menuState = new MenuState();
	this->audioManager = AudioManager::GetInstance();
}


MainStateMachine::~MainStateMachine()
{
	delete this->gameState;
	delete this->gameOverState;
	delete this->winState;
	delete this->menuState;
	//delete this->audioManager;
}

void MainStateMachine::Update(double deltaTime)
{
	if (timePassed < 10.0f)
		timePassed += (float)deltaTime;

	audioManager->Update(deltaTime);

	if (Input::GetInstance()->IsKeyPressed(KEY_X) && timePassed > 0.2f)
	{
		timePassed = 0;
		
	}
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
	else if (winState->isActive)
	{
		winState->Update(deltaTime);
	}
	
	if (this->activeState == MAIN_GAME_STATE && gameState->isPlayerDead == true)
	{
		gameState->isActive = false;
		audioManager->stopAmbientGameStateSound();
		audioManager->playLoseLoop();

		if (gameOverState)
		{
			gameOverState->Release();
			delete gameOverState;
		}

		this->gameOverState = new GameOverState();
		gameOverState->Initialize();
		gameOverState->isActive = true;
		gameOverState->SetLastHigh(lastHighscore);
		float points1 = gameState->GetPoints();
		gameOverState->SetPoints(points1);

		if (lastHighscore < gameState->GetPoints())
		{
			lastHighscore = gameState->GetPoints();
			gameOverState->SetLastHigh(lastHighscore);
		}


		
		this->activeState = MAIN_GAMEOVER_STATE;

	}
	if (this->activeState == MAIN_GAME_STATE && gameState->toWin == true)
	{
		gameState->isActive = false;
		audioManager->stopAmbientGameStateSound();
		audioManager->playWinLoop();

		if (winState)
		{
			winState->Release();
			delete winState;
		}
		this->winState = new WinState();
		winState->Initialize();
		winState->isActive = true;
		winState->SetLastHigh(lastHighscore);
		//float points1 = gameState->GetPoints();
		winState->SetPoints(gameState->GetPoints());

		if (lastHighscore < gameState->GetPoints())
		{
			lastHighscore = gameState->GetPoints();
			winState->SetLastHigh(lastHighscore);

		}

		this->activeState = MAIN_WIN_STATE;

	}
	if (this->activeState == MAIN_GAME_STATE && gameState->toMenu == true)
	{
		audioManager->playMainMenuLoop();
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
		audioManager->stopMainMenuLoop();

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
		audioManager->playInGameLoop();
		audioManager->stopLoseLoop();
		audioManager->stopWinLoop();
		

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
		audioManager->stopLoseLoop();
		//audioManager->stopWinLoop();
		audioManager->playMainMenuLoop();

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

	if (this->activeState == MAIN_WIN_STATE && winState->replay == true)
	{
		winState->isActive = false;
		audioManager->stopWinLoop();
		audioManager->playInGameLoop();

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
	else if (this->activeState == MAIN_WIN_STATE && winState->toMenu == true)
	{
		winState->isActive = false;
		audioManager->stopWinLoop();
		audioManager->playMainMenuLoop();

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
	else if (winState->isActive)
	{
		winState->Render();
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
	this->winState->isActive = false;
	this->gameOverState->isActive = false;
	this->menuState->isActive = false;
	gameState->toMenu = true;
	this->delay = 0.0f;
	this->lastHighscore = 0.0f;
	gameState->toMenu = true;
	timePassed = 0;
}

void MainStateMachine::Release()
{
	audioManager->Release();
}
