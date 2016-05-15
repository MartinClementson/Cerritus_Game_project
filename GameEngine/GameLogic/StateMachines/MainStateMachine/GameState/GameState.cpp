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

void GameState::Initialize(AudioManager* audioManager)
{
	this->audioManager = audioManager;
	input->Initialize();
	player->Initialize(audioManager);
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
	index = 5.0f;
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
	index += (float)deltaTime;
	healers.clear();
	ProcessInput(&deltaTime);
	gameUI->Update(deltaTime);
	ProcessInput(&deltaTime);
	if (!pause->isActive)
	{
		this->bearTraps = room1->bearTraps;
		this->fireTraps = room1->fireTraps;

		gameUI->setUI(UITextures::HUD);

		if (player->GetHealth() <= 0)
		{
			isPlayerDead = true;
			//isActive = false;
		}
		XMFLOAT2 mouseXY = input->GetMousePosition();

		XMFLOAT3 dir = Graphics::GetInstance()->GetPlayerDirection(mouseXY, player->GetPosition());

		player->Update(deltaTime, dir);

		//finding all healers

		for (size_t k = 0; k < room1->enemySpawns.size(); k++)
		{
			size_t j = 0;
			while (j < room1->enemySpawns.at(k)->StandardAlive.size())
			{
				if (room1->enemySpawns.at(k)->StandardAlive.at(j)->
					GetCharType() == CharacterType::HEALER
					&& room1->enemySpawns.at(k)->StandardAlive.at(j)->isAlive)
				{
					healers.push_back(room1->enemySpawns.at(k)->StandardAlive.at(j));
					//((Enemy*)room1->enemySpawns.at(k)->StandardAlive.at(j))->SetClosestHealer(healers.at(0));
				}
				
				j++;
			}
		}

		if (healers.size() == (size_t)0)
		{
			healers.push_back(nullptr);
		}

		for (size_t k = 0; k < room1->enemySpawns.size(); k++)
		{
			size_t j = 0;
			while (j < room1->enemySpawns.at(k)->StandardAlive.size())
			{
				
				room1->enemySpawns.at(k)->StandardAlive.at(j)->SetClosestHealer(healers.at(0));
				j++;
			}
		}

		for (size_t i = 0; i < room1->WeaponUpgrades.size(); i++)
		{
			if (collision->WeaponPickupCollision(room1->WeaponUpgrades.at(i)))
			{
				if (room1->WeaponUpgrades.at(i)->GetPickupType() == PickupType::WEAPON)
				{
					this->player->UpgradeWeapon();
					room1->WeaponUpgrades.at(i)->SetIsActive(false);
				}
				else if (room1->WeaponUpgrades.at(i)->GetPickupType() == PickupType::HEAL)
				{
					this->player->SetHealth(player->GetHealth() + 50);

					if (player->GetHealth() > player->GetMaxHealth())
					{
						player->SetHealth(player->GetMaxHealth());
					}

					room1->WeaponUpgrades.at(i)->SetIsActive(false);
				}
			}
		}

		

		for (size_t k = 0; k < room1->enemySpawns.size(); k++)
		{
			size_t j = 0;
			while (j < room1->enemySpawns.at(k)->StandardAlive.size())
			{
				for (size_t p = 0; p < room1->enemySpawns
					.at(k)->StandardAlive.size(); p++)
				{
					size_t i = 0;
					while (i < player->projectileSystem->GetFiredProjectiles())
					{
						if (collision->ProjectileEnemyCollision(
							player->projectileSystem->
							projectiles[i],

							room1->enemySpawns.at(k)->
							StandardAlive.at(j))

							&& room1->enemySpawns.at(k)->
							StandardAlive.at(j)->isAlive == true

							&& player->projectileSystem->
							projectiles[i]->GetFired() == true)
						{
							room1->enemySpawns.at(k)->StandardAlive.at(j)->SetHealth(
								room1->enemySpawns.at(k)->StandardAlive.at(j)->
								GetHealth() - 10);
							player->projectileSystem->
								projectiles[i]->SetFired(false);
						}
						i++;
					}
					if (room1->enemySpawns.at(k)->StandardAlive.at(p)->isAlive == true)
					{
						//float maxHealth = room1->enemySpawns.at(k)->StandardAlive.at(j)->GetMaxHealth();

						if (room1->enemySpawns.at(k)->StandardAlive.at(j)->GetStateMachine()->
							GetActiveState() == ENEMY_HEAL_STATE
							&& 
							room1->enemySpawns.at(k)->StandardAlive.at(j)->
							GetCharType() != CharacterType::HEALER
							&&
							healers.at(0) != nullptr)
						{

							EnemyBase* tmpCloseHealer = nullptr;


							XMFLOAT3 position;
							position = room1->enemySpawns.at(k)->StandardAlive.at(j)->position;

							XMFLOAT3 healPos;
							healPos.y = 0;
							XMFLOAT3 closest;
							closest.x = 1000;
							closest.y = 0;
							closest.z = 1000;
							XMFLOAT3 tmp;
							tmp.y = 0;

							//tmpCloseHealer = healers.at(0);

							if (healers.at(0) != nullptr)
							{
								for (size_t i = 0; i < healers.size(); i++)
								{
									healPos = healers.at(i)->position;

									//////////////////
									if (healers.at(i)->isAlive)
									{
										//if (healers.at(i)->healing < 7)
										//{
											tmp.x = healPos.x - position.x;
											if (tmp.x < 0)
											{
												tmp.x = -tmp.x;
											}
											tmp.z = healPos.z - position.z;
											if (tmp.z < 0)
											{
												tmp.z = -tmp.z;
											}

											//////////////////



											if (closest.x > tmp.x && closest.z > tmp.z && healers.at(i)->isAlive)
											{
												closest = tmp;
												tmpCloseHealer = healers.at(i);
											}
										//}
									}

								}
							}


							
							room1->enemySpawns.at(k)->StandardAlive.at(j)->SetClosestHealer(tmpCloseHealer);


						
							if (tmpCloseHealer)
							{
								tmpCloseHealer->healing += 1;

								room1->enemySpawns.at(k)->StandardAlive.at(p)->AIPatternHeal(
									tmpCloseHealer,
									deltaTime);


								if (collision->HealerProximity(room1->enemySpawns.at(k)->
									StandardAlive.at(p), tmpCloseHealer))
								{
									if (room1->enemySpawns.at(k)->StandardAlive.at(j)->GetStateMachine()->
										GetActiveState() == ENEMY_HEAL_STATE
										&& room1->enemySpawns.at(k)->StandardAlive.at(j)->GetCharType() != CharacterType::HEALER)
									{
										/*room1->enemySpawns.at(k)->
											StandardAlive.at(p)->SetHealth(
												room1->enemySpawns.at(k)->
												StandardAlive.at(p)->
												GetHealth() + 1.0f);*/
									}
								}
								
								
							}
							else
							{
								room1->enemySpawns.at(k)->StandardAlive.at(p)->AIPattern(
									collision->GetPlayer(),
									deltaTime);
								room1->enemySpawns.at(k)->
									StandardAlive.at(p)->isBeingHealed = false;
							}
						}
						else
						{
							if (j == p || collision->PlayerDistanceCollision(
								room1->enemySpawns.at(k)->StandardAlive.at(p)))
							{
								room1->enemySpawns.at(k)->StandardAlive.at(p)->AIPattern(
									collision->GetPlayer(),
									deltaTime);
							}
							else if (collision->EnemyCollision(
								room1->enemySpawns.at(k)->StandardAlive.at(p),
								room1->enemySpawns.at(k)->StandardAlive.at(j)))
							{
								if (room1->enemySpawns.at(k)->StandardAlive.at(j)->
									GetCharType() != CharacterType::HEALER)
								{
									room1->enemySpawns.at(k)->StandardAlive.at(p)->EnemyWithEnemyCollision(
										room1->enemySpawns.at(k)->StandardAlive.at(p),
										room1->enemySpawns.at(k)->StandardAlive.at(j),
										deltaTime);
								}
							}
							/*else if (collision->TrapandEnemyLottery(room1->enemySpawns.at(k)->StandardAlive.at(p)))
							{
								for (size_t i = 0; i < room1->bearTraps.size(); i++)
								{
									int randoms = rand() % 100 + 1;

									if (randoms == 1 && room1->bearTraps.at(i)->isActive)
									{
										room1->EvadeTrap(room1->enemySpawns.at(k)->StandardAlive.at(p)
											, room1->bearTraps.at(i), deltaTime);
									}
								}
							}*/
						}	
					}
				}
				j++;
			}
		}
		room1->Update(deltaTime);
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
		int					 moveKeysPressed		 = 0;		//How many have been clicked
		int					 maxMoveKeysPressed		 = 2;		// Maximum amount of movement keys that can be clicked each frame.

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

		for (size_t i = 0; i < bearTraps.size(); i++)
		{
			if (input->IsKeyPressed(KEY_Q) && collision->BearTrapActivation(bearTraps.at(i)))
			{
				bearTraps.at(i)->GetState()->SetTrapState(TrapState::TRAP_IDLE_STATE);
			}
		}

		for (size_t i = 0; i < fireTraps.size(); i++)
		{
			if (input->IsKeyPressed(KEY_Q) && collision->FireTrapActivation(fireTraps.at(i)))
			{
				fireTraps.at(i)->GetState()->SetTrapState(TrapState::TRAP_IDLE_STATE);
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
		if (input->IsKeyPressed(KEY_Z))
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