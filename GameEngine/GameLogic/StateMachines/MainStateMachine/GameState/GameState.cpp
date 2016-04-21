#include "GameState.h"



GameState::GameState()
{
	this->death = new MainDeathState();
	this->pause = new MainPausedState();
	this->player = new Player();
	this->input = Input::GetInstance();
	this->room1 = new Scene();
	this->collision = Collision::GetInstance();
}


GameState::~GameState()
{
	delete this->death;
	delete this->pause;
	delete this->player;
	delete this->room1;

}

void GameState::Initialize()
{
	input->Initialize();
	player->Initialize();
	death->Initialize();
	pause->Initialize();
	death->isActive = false;
	pause->isActive = false;
	room1->Initialize();
	OnEnter();

}

void GameState::Release()
{
	death->Release();
	pause->Release();
	input->Release();
	player->Release();
	room1->Release();

}

void GameState::Update(double deltaTime)
{
	ProcessInput(&deltaTime);
	XMFLOAT2 mouseXY = input->GetMousePosition();

	XMFLOAT3 dir = Graphics::GetInstance()->GetPlayerDirection( mouseXY, player->GetPosition());
	
		
	player->Update(deltaTime,dir);
	collision;

	room1->Update(deltaTime);

}

void GameState::ProcessInput(double* deltaTime)
{
	XMFLOAT2 temp = input->GetMousePosition();

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
		if (input->IsKeyPressed(KEY_W))
	
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
		else if (input->IsKeyPressed(KEY_SPACE))
		{
			player->Shoot(KEY_SPACE, deltaTime[0]);
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
	collision->AddPlayer(this->player);

}

void GameState::OnExit()
{

}
