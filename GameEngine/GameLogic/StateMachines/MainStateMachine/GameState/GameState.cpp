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
	this->menu = new MenuState();
	this->gameUI = new GUI();
}


GameState::~GameState()
{
	delete this->death;
	delete this->pause;
	delete this->player;
	delete this->room1;
	delete this->menu;
	delete this->gameUI;

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
	toMenu = false;
	menu->Initialize();
	menu->isActive = false;
	gameUI->Initialize();
	//Create room one here
	timeSincePaused = 0.0f;
	room1->Initialize();
	room1->InitBearTrap();
	room1->InitFireTrap();
	room1->AddEnemySpawn(XMFLOAT3(30.0f, 0.0f, 20.0f));
	room1->AddEnemySpawn(XMFLOAT3(-50.0f, 0.0f, -50.0f));
	room1->AddEnemySpawn(XMFLOAT3(-50.0f, 0.0f, 30.0f));
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
	menu->Release();
	gameUI->Release();
}

void GameState::Update(double deltaTime)
{
	gameUI->Update(deltaTime);
	ProcessInput(&deltaTime);
	if (!pause->isActive)
	{
		gameUI->setUI(UITextures::HUD);

		if (player->GetHealth() <= 0)
		{
			isPlayerDead = true;
			//isActive = false;
		}
		XMFLOAT2 mouseXY = input->GetMousePosition();

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
						if (j == p || collision->PlayerDistanceCollision(
							room1->enemySpawns.at(k)->Alive.at(p)))
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
								int randoms = rand() % 100 + 1;

								if (randoms == 1 && room1->bearTraps.at(i)->isActive)
								{
									room1->EvadeTrap(room1->enemySpawns.at(k)->Alive.at(p)
										, room1->bearTraps.at(i), deltaTime);
								}

							}
						}

						

					}
				}
				j++;
			}
		}

		size_t i = 0; 
		while (i < player->projectileSystem->GetFiredProjectiles())
		{
			for (size_t k = 0; k < room1->enemySpawns.size(); k++)
			{

				size_t j = 0;
				while (j < room1->enemySpawns.at(k)->Alive.size())
				{
					if (collision->ProjectileEnemyCollision(
						player->projectileSystem->
						projectiles[i],

						room1->enemySpawns.at(k)->
						Alive.at(j))

						&& room1->enemySpawns.at(k)->
						Alive.at(j)->isAlive == true)
					{
						room1->enemySpawns.at(k)->Alive.at(j)->SetHealth(
							room1->enemySpawns.at(k)->Alive.at(j)->GetHealth() - 10);
						player->projectileSystem->projectiles[i]->SetFired(false);
					}


					j++;
				}
			}
			i++;
		}
	}
	else if (pause->isActive)
	{
		gameUI->setUI(UITextures::PAUSE);
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

		int					 moveKeysPressed = 0;		//How many have been clicked
		int					 maxMoveKeysPressed = 2;		// Maximum amount of movement keys that can be clicked each frame.
		MovementDirection	 directions[2];						//This should be as big as MaxMoveKeysPressed

#pragma region Movement Keys

		if (input->IsKeyPressed(KEY_W))
		{
			directions[moveKeysPressed] = UP;
			moveKeysPressed += 1;

		}


		if (input->IsKeyPressed(KEY_S))
		{
			if (moveKeysPressed < maxMoveKeysPressed)
			{
				directions[moveKeysPressed] = DOWN;
				moveKeysPressed += 1;
			}


		}

		if (input->IsKeyPressed(KEY_A))
		{
			if (moveKeysPressed < maxMoveKeysPressed)
			{
				directions[moveKeysPressed] = LEFT;
				moveKeysPressed += 1;
			}

		}


		if (input->IsKeyPressed(KEY_D))
		{
			if (moveKeysPressed < maxMoveKeysPressed)
			{
				directions[moveKeysPressed] = RIGHT;
				moveKeysPressed += 1;
			}
		}


		if (moveKeysPressed > 0)
		{
			player->Move(directions, moveKeysPressed, deltaTime[0]);
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
		else if (input->IsKeyPressed(KEY_Z))
		{
			player->Shoot(KEY_Z, deltaTime[0]);
		}
		else if (input->IsKeyPressed(KEY_X))
		{
			player->Shoot(KEY_X, deltaTime[0]);
		}
		else if (input->IsKeyPressed(KEY_C))
		{
			player->Shoot(KEY_C, deltaTime[0]);
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