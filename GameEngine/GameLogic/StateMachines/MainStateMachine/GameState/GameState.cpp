#include "GameState.h"



GameState::GameState()
{
	this->death = new MainDeathState();
	this->pause = new MainPausedState();
	this->player = new Player();
	this->input = Input::GetInstance();
<<<<<<< HEAD
	//this->enemy = new Enemy();
	//this->enemyState = new EnemyState();
=======
	this->enemy = new Enemy();
	this->room1 = new Scene();
>>>>>>> refs/remotes/origin/Game-Logic-Sebbe

}


GameState::~GameState()
{
	delete this->death;
	delete this->pause;
	delete this->player;
<<<<<<< HEAD
	//delete this->enemy;
	//delete this->enemyState;

=======
	delete this->enemy;
	delete this->room1;
>>>>>>> refs/remotes/origin/Game-Logic-Sebbe
}

void GameState::Initialize()
{
	input->Initialize();
	player->Initialize();
	death->Initialize();
	pause->Initialize();
	death->isActive = false;
	pause->isActive = false;
	enemyState->Initialize();

	room1->Initialize();
	enemy->Initialize();
}

void GameState::Release()
{
	death->Release();
	pause->Release();
	input->Release();
	player->Release();
	room1->Release();
	//enemy->Release();
}

void GameState::Update(double deltaTime)
{
	ProcessInput(&deltaTime);
	player->Update(deltaTime);
	enemyState->Update(deltaTime);
	enemy->Update(deltaTime);
	room1->Update(deltaTime);

}

void GameState::ProcessInput(double* deltaTime)
{

	if (death->isActive)
	{

	}
	else if (pause->isActive)
	{
		if (input->IsKeyPressed(KEY_ESC))
		{
			pause->isActive = false;
		}
	}
	else
	{
		if (input->IsKeyHeld(KEY_W))
	
		{
			player->Move(UP, deltaTime[0]);
		}
		else if (input->IsKeyPressed(KEY_S))
		{
			player->Move(DOWN, deltaTime[0]);
		}
		else if (input->IsKeyPressed(KEY_A))
		{
			player->Move(LEFT, deltaTime[0]);
		}
		else if (input->IsKeyPressed(KEY_D))
		{
			player->Move(RIGHT, deltaTime[0]);
		}
		else if (input->IsKeyPressed(KEY_ESC))
		{
			pause->isActive = true;
		}
	}
}

void GameState::Render()
{
	room1->Render();
	player->Render();
	gameUI->Render();

	enemy->Render();
}

void GameState::OnEnter()
{

}

void GameState::OnExit()
{

}
