#include "GameState.h"



GameState::GameState()
{
}


GameState::~GameState()
{
}

void GameState::Initialize()
{
}

void GameState::Release()
{
}

void GameState::Update(double deltaTime)
{
	ProcessInput(deltaTime);
	player->Update(deltaTime);
}

void GameState::ProcessInput(double deltaTime)
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
			player->Move(UP, deltaTime);
		}
		else if (input->IsKeyHeld(KEY_S))
		{
			player->Move(DOWN, deltaTime);
		}
		else if (input->IsKeyHeld(KEY_A))
		{
			player->Move(LEFT, deltaTime);
		}
		else if (input->IsKeyHeld(KEY_D))
		{
			player->Move(RIGHT, deltaTime);
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
}

void GameState::OnEnter()
{
}

void GameState::OnExit()
{
}
