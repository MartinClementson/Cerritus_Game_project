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

	room1->Update(deltaTime);
	int i = 0;
	
	while(i < player->projectileSystem->projectiles.size())
	{
		int j = 0;
		while(j<room1->enemySpawn->Alive.size())
		{
			if (collision->ProjectileEnemyCollision(
				player->projectileSystem->
				projectiles.at(i),

				room1->enemySpawn->
				Alive.at(j))

				&& room1->enemySpawn->
				Alive.at(j)->isAlive == true)
			{
				//not alive anymore
				//MessageBox(0, L"You have Collided",
				//	L"LOL", MB_OK);

				room1->enemySpawn->Alive.at(j)->isAlive = false;

				room1->enemySpawn->
					Queue.push_back(
						room1->enemySpawn->
						Alive.at(j)
					);

				room1->enemySpawn->
					Alive.erase(
						room1->enemySpawn->
						Alive.begin() + j
					);

				
				/*if (player->projectileSystem->projectiles.size() >0)
				{
					player->projectileSystem->DeleteProjectile(i);
				}*/
				
				
			}
			j++;
		}
		i++;
	}
	
	
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
		int					 moveKeysPressed		 = 0;		//How many have been clicked
		int					 maxMoveKeysPressed		 = 2;		// Maximum amount of movement keys that can be clicked each frame.
		MovementDirection	 directions[2];						//This should be as big as MaxMoveKeysPressed

#pragma region Movement Keys

		if (input->IsKeyPressed(KEY_W))
		{
			directions[moveKeysPressed]  = UP;
			moveKeysPressed				+= 1;
			
		}


		if (input->IsKeyPressed(KEY_S))
		{
			if (moveKeysPressed < maxMoveKeysPressed)
			{
				directions[moveKeysPressed]				 = DOWN;
				moveKeysPressed							 += 1;
			}
			

		}

		if (input->IsKeyPressed(KEY_A))
		{
			if (moveKeysPressed < maxMoveKeysPressed)
			{
				directions[moveKeysPressed]		 = LEFT;
				moveKeysPressed += 1;
			}
			
		}


		if (input->IsKeyPressed(KEY_D))
		{
			if (moveKeysPressed < maxMoveKeysPressed)
			{
				directions[moveKeysPressed]		 = RIGHT;
				moveKeysPressed					 += 1;
			}
		}


		if (moveKeysPressed > 0)
		{

			player->Move(directions, moveKeysPressed ,deltaTime[0]);

		}

#pragma endregion


		if (input->IsKeyPressed(KEY_ESC))
		{
			pause->isActive = true;
		}

		if (input->IsKeyPressed(KEY_SPACE))
		{
			player->Shoot(KEY_SPACE, deltaTime[0]);
		}
		else if (input->isMouseClicked(MOUSE_LEFT))
		{
			player->Shoot(MOUSE_LEFT, deltaTime[0]);
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
