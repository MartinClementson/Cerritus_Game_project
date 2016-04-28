#include "GameState.h"



GameState::GameState()
{
	this->death = new MainDeathState();
	this->pause = new MainPausedState();
	this->player = new Player();
	this->input = Input::GetInstance();
	this->room1 = new Scene();
	this->collision = Collision::GetInstance();
	this->gameTimer = GameTimer::GetInstance();
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
	isPlayerDead = false;
	//Create room one here
	timeSincePaused = 0.0f;
	room1->Initialize();
	room1->InitBearTrap();
	room1->InitFireTrap();
	room1->AddEnemySpawn(XMFLOAT3( 10.0f, 0.0f,  5.0f));
	room1->AddEnemySpawn(XMFLOAT3(-30.0f, 0.0f, -20.0f));
	room1->AddEnemySpawn(XMFLOAT3(0.0f, 0.0f, -50.0f));
	index = 0;
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
	if (!pause->isActive)
	{

		if (player->GetHealth() <= 0)
		{
			isPlayerDead = true;
			//isActive = false;
		}
		ProcessInput(&deltaTime);
		XMFLOAT2 mouseXY = input->GetMousePosition();

		XMFLOAT3 dir = Graphics::GetInstance()->GetPlayerDirection(mouseXY, player->GetPosition());

		for (size_t j = 0; j < room1->enemySpawns.size(); j++)
		{

			for (size_t i = 0; i < room1->enemySpawns.at(j)->Alive.size(); i++)
			{
				room1->enemySpawns.at(j)->Alive.at(i)->AIPattern(player, deltaTime);
			}
		}


		player->Update(deltaTime, dir);

		room1->Update(deltaTime);

		size_t i = 0;
		while (i < player->projectileSystem->projectiles.size())
		{
			for (size_t k = 0; k < room1->enemySpawns.size(); k++)
			{

				size_t j = 0;
				while (j < room1->enemySpawns.at(k)->Alive.size())
				{
					if (collision->ProjectileEnemyCollision(
						player->projectileSystem->
						projectiles.at(i),

						room1->enemySpawns.at(k)->
						Alive.at(j))

						&& room1->enemySpawns.at(k)->
						Alive.at(j)->isAlive == true)

	XMFLOAT3 dir = Graphics::GetInstance()->GetPlayerDirection(mouseXY, player->GetPosition());

	player->Update(deltaTime, dir);

	room1->Update(deltaTime);

	for (size_t k = 0; k < room1->enemySpawns.size(); k++)
	{
		size_t j = 0;
		while (j < room1->enemySpawns.at(k)->Alive.size())
		{
			for (size_t p = 0; p < room1->enemySpawns
				.at(k)->Alive.size(); p++)
			{
				if (room1->enemySpawns.at(k)->Alive.at(p)->isAlive == true)
				{
					if (j == p)
					{
						room1->enemySpawns.at(k)->Alive.at(p)->AIPattern(
							collision->GetPlayer(),
							deltaTime);
					}
					else if (collision->EnemyCollision(
						room1->enemySpawns.at(k)->Alive.at(p),
						room1->enemySpawns.at(k)->Alive.at(p))


						&& collision->PlayerDistanceCollision(
							room1->enemySpawns.at(k)->Alive.at(p))
						&& j == p
						)
					{
						room1->enemySpawns.at(k)->Alive.at(p)->AIPattern(
							collision->GetPlayer(),
							deltaTime);
					}

					else if (collision->EnemyCollision(
						room1->enemySpawns.at(k)->Alive.at(p),
						room1->enemySpawns.at(k)->Alive.at(j)))
					{
						room1->enemySpawns.at(k)->Alive.at(p)->EnemyWithEnemyCollision(
							room1->enemySpawns.at(k)->Alive.at(p),
							room1->enemySpawns.at(k)->Alive.at(j),
							deltaTime);
					}
					else if (collision->TrapandEnemyLottery(room1->enemySpawns.at(k)->Alive.at(p)))
					{
						for (size_t i = 0; i < room1->bearTraps.size(); i++)
						{
							/*int randoms = rand() % 5 + 1;

							if (randoms == 1 && room1->bearTraps.at(i)->isActive)
							{*/
								room1->EvadeTrap(room1->enemySpawns.at(k)->Alive.at(p)
									, room1->bearTraps.at(i), deltaTime);
							/*}*/

						}
					}
					
						/*	else
							{
								room1->enemySpawns.at(k)->Alive.at(p)->AIPattern(
									collision->GetPlayer(),
									deltaTime);
							}*/
					
				}
			}
			j++;
		}
	}

	size_t i = 0;
	while (i < player->projectileSystem->projectiles.size())
	{
		for (size_t k = 0; k < room1->enemySpawns.size(); k++)
		{
			size_t j = 0;
			while (j < room1->enemySpawns.at(k)->Alive.size())
			{
				if (collision->ProjectileEnemyCollision(
					player->projectileSystem->
					projectiles.at(i),

					room1->enemySpawns.at(k)->
					Alive.at(j))

					&& room1->enemySpawns.at(k)->
					Alive.at(j)->isAlive == true)
				{
					//not alive anymore
					//MessageBox(0, L"You have Collided",
					//	L"LOL", MB_OK);
					if (room1->enemySpawns.at(k)->Alive.at(j)->GetHealth() <= 10.0f)
					{
						room1->enemySpawns.at(k)->Alive.at(j)->isAlive = false;
						room1->enemySpawns.at(k)->Alive.at(j)->SetHealth(100.0f);

						room1->enemySpawns.at(k)->
							Queue.push_back(
								room1->enemySpawns.at(k)->
								Alive.at(j)
							);

						room1->enemySpawns.at(k)->
							Alive.erase(
								room1->enemySpawns.at(k)->
								Alive.begin() + j
							);

					}
					else
					{
						float tmpEnemyHealth = room1->enemySpawns.at(k)->Alive.at(j)->GetHealth();
						room1->enemySpawns.at(k)->Alive.at(j)->SetHealth(tmpEnemyHealth - 30.0f);
					}
					if (player->projectileSystem->projectiles.size() > 0)
					{
						if(room1->enemySpawns.at(k)->Alive.at(j)->GetHealth() > 0.0f)
						{
							float tmpEnemyHealth = room1->enemySpawns.at(k)->Alive.at(j)->GetHealth();
							room1->enemySpawns.at(k)->Alive.at(j)->SetHealth(tmpEnemyHealth - 30.0f);
						}
						if (player->projectileSystem->projectiles.size() > 0)
						{
							player->projectileSystem->projectiles.at(i)->SetFired(false);
						}


					}
//<<<<<<< HEAD
					j++;
				}
			}
			i++;
		}
		/*if (index < 1)
		{
			index++;
//=======


				}
				j++;
			}

//>>>>>>> refs/remotes/origin/Game-Logic-Johan
		}
		else if (index == 1)
		{
			pause->isActive = true;
			index++;
		}*/
	}

}
	

void GameState::ProcessInput(double* deltaTime)
{
	timeSincePaused += (float)*deltaTime;
	XMFLOAT2 temp = input->GetMousePosition();
	
	if (death->isActive)
	{

	}
	else if (pause->isActive)
	{
		if (input->IsKeyPressed(KEY_ENTER) && timeSincePaused > 0.2f)
		{
			pause->isActive = false;
			timeSincePaused = 0.0f;
			
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


		if (input->IsKeyPressed(KEY_ENTER) && timeSincePaused >0.2f)
		{
			pause->isActive = true;
			timeSincePaused = 0.0f;
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

void GameState::SetIsActive(bool isPlayerDead)
{
	this->isPlayerDead = isPlayerDead;
}

bool GameState::GetIsActive()
{
	return isPlayerDead;
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

float GameState::GetPoints()
{
	return player->GetPoints();
}