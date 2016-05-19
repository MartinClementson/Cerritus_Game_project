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
	currentTime = 0;
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
	room1->Initialize(audioManager);
	room1->InitBearTrap();
	room1->InitFireTrap();

	index = 0;
	collision->InitSceneCol();
	Input::GetInstance()->SetMouseVisibility(false);

	index = 5.0f;
	//test = 1;
	//AntTweakBar::GetInstance()->addSlider("testGameState", test);

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

		player->Update(deltaTime, dir, (collision->SceneColIn(deltaTime)));

		room1->Update(deltaTime);

		if (room1->toWin == true)
		{
			toWin = true;
		}

		size_t j = 0;
		while (j < room1->enemySpawn->GetNrAliveEnemies())
		{
			if (room1->enemySpawn->Alive[j]->
				GetCharType() == CharacterType::HEALER
				&& room1->enemySpawn->Alive[j]->isAlive)
			{
				healers.push_back(room1->enemySpawn->Alive[j]);
			}

			j++;
		}

		if (healers.size() == (size_t)0)
		{
			healers.push_back(nullptr);
		}

		for (size_t i = 0; i < room1->Pickups.size(); i++)
		{
			if (collision->WeaponPickupCollision(room1->Pickups.at(i)))
			{

				if (room1->Pickups.at(i)->GetPickupType() == PickupType::WEAPON)
				{
					audioManager->playWeaponPickup();
					this->player->UpgradeWeapon();
					room1->Pickups.at(i)->SetIsActive(false);
				}

				else if (room1->Pickups.at(i)->GetPickupType() == PickupType::HEAL)
				{
					audioManager->playHealthPickup();
					this->player->SetHealth(player->GetHealth() + 50);

					if (player->GetHealth() > player->GetMaxHealth())
					{
						player->SetHealth(player->GetMaxHealth());
					}

					room1->Pickups.at(i)->SetIsActive(false);
				}
			}
		}

		if (healers.size() > 0)
		{
			for (int j = 0; j < room1->enemySpawn->GetNrAliveEnemies(); ++j)
			{
				room1->enemySpawn->Alive[j]->SetClosestHealer(healers.at(0));
			}
		}
		//j = 0;
		//while (j < room1->enemySpawn->Alive.size())
		//{
			for (size_t p = 0; p < room1->enemySpawn->GetNrAliveEnemies(); p++)
			{
				if (room1->enemySpawn->Alive[p]->isAlive == true)
				{
					if (room1->enemySpawn->Alive[p]->GetStateMachine()->
						GetActiveState() == ENEMY_HEAL_STATE
						&&
						room1->enemySpawn->Alive[p]->
						GetCharType() != CharacterType::HEALER
						&&
						healers.at(0) != nullptr
						&& room1->enemySpawn->Alive.at(p)->healable != false)
					{
						
						EnemyBase* tmpCloseHealer = nullptr;
						XMFLOAT3 position;
						position = room1->enemySpawn->Alive[p]->position;
						XMFLOAT3 healPos;
						healPos.y = 0;
						Vec3 closest;
						closest.x = 1000;
						closest.y = 0;
						closest.z = 1000;
						Vec3 tmp;
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
									//if (tmp.x < 0)
									//{
									//	tmp.x = -tmp.x;
									//}
									tmp.z = healPos.z - position.z;
									//if (tmp.z < 0)
									//{

									//	tmp.z = -tmp.z;


									//}
									if (tmp.Length() < closest.Length() && healers.at(i)->isAlive)
									{
										closest = tmp;
										tmpCloseHealer = healers.at(i);
									}
									//}
								}


							}
						}
					

						room1->enemySpawn->Alive[p]->SetClosestHealer(tmpCloseHealer);

						if (tmpCloseHealer)
						{
							//tmpCloseHealer->healing += 1;


							room1->enemySpawn->Alive[p]->AIPatternHeal(
								tmpCloseHealer,
								deltaTime);

							if (collision->HealerProximity(room1->enemySpawn->
								Alive[p], tmpCloseHealer))
							{
								if (room1->enemySpawn->Alive[p]->GetCharType() != CharacterType::HEALER)
								{
									room1->enemySpawn->
										Alive[p]->SetHealth(
											room1->enemySpawn->
											Alive[p]->
											GetHealth() + 1.0f);
								}

							}
						}
						
					}
					
				}
			}
			//j++;
		//}
		
		for (int p = 0; p < room1->enemySpawn->GetNrAliveEnemies(); p++)
		{
			if (room1->enemySpawn->Alive[p]->isAlive)
			{
				for (int j = p + 1; j < room1->enemySpawn->GetNrAliveEnemies(); j++)
				{
					if (room1->enemySpawn->Alive[j]->isAlive)
					{
						if (collision->PlayerDistanceCollision(
							room1->enemySpawn->Alive[p]))
						{
							room1->enemySpawn->Alive[p]->AIPattern(
								collision->GetPlayer(),
								deltaTime);
							//audioManager->playPlayerHit();
						}

						else if (collision->EnemyCollision(
							room1->enemySpawn->Alive[p],
							room1->enemySpawn->Alive[j]))
						{
							room1->enemySpawn->Alive[p]->EnemyWithEnemyCollision(
								room1->enemySpawn->Alive[p],
								room1->enemySpawn->Alive[j],
								deltaTime);
						}
					}
				}
				if (room1->enemySpawn->Alive[p]->GetStateMachine()->GetActiveState() == ENEMY_ATTACK_STATE)
				room1->enemySpawn->Alive[p]->AIPattern(
					collision->GetPlayer(),
					deltaTime);
			}
		}
		size_t i = 0; //kolla in denna efter du fixat renderingen
		while (i < player->projectileSystem->GetFiredProjectiles())
		{
			size_t j = 0;
			while (j <  room1->enemySpawn->GetNrAliveEnemies())
			{
				if (collision->ProjectileEnemyCollision(
					player->projectileSystem->
					projectiles[i],

					room1->enemySpawn->
					Alive[j])

					&& room1->enemySpawn->
					Alive[j]->isAlive == true)
				{
					room1->enemySpawn->Alive[j]->SetHealth(
						room1->enemySpawn->Alive[j]->GetHealth() - 5.0f);
					player->projectileSystem->projectiles[i]->SetFired(false);
					if (room1->enemySpawn->Alive[j]->GetHealth() == 0)
								audioManager->playEDeathSound();
				}


				j++;
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
	timer += (float)*deltaTime;
	XMFLOAT2 temp = input->GetMousePosition();

	/*if (input->IsKeyPressed(KEY_X) && timeSincePaused > 0.2f)
	{
		timeSincePaused = 0;
		AntTweakBar::GetInstance()->toggleShowingBar();
	}*/

	if (death->isActive)
	{

	}
	else if (pause->isActive)
	{
		gameUI->setUI(UITextures::PAUSE);

		XMFLOAT2 mousePos = InputHandler::GetInstance()->GetMousePosition();

		float vx = ((2.0f * mousePos.x) / (float)WIN_HEIGHT - 1.0f);
		float vy = ((2.0f * -mousePos.y) / (float)WIN_WIDTH + 1.0f);

		if (vx > Maxex && vy < Maxey && vx < Minex && vy > Miney)
		{

			if (input->isMouseClicked(MOUSE_LEFT))
			{

				toMenu = true;
				menu->isActive = true;
				//pause->isActive = false;
			}

			//shutofgame, release everything no memory leaks are allowed
			//OnExit();
		}
		else if (vx > Maxnx && vy < Maxny && vx < Minnx && vy > Minny)
		{
			if (input->isMouseClicked(MOUSE_LEFT))
			{
				pause->isActive = false;
				gameUI->setUI(UITextures::HUD);
			}
		}
		else if (vx > Maxcx && vy < Maxcy && vx < Mincx && vy > Mincy)
		{
			if (input->isMouseClicked(MOUSE_LEFT))
			{
				pause->isActive = false;

				NewGame();

				isActive = true;

				this->activeState = MAIN_GAME_STATE;
			}
		}
		if (input->IsKeyPressed(KEY_ESC) && timeSincePaused > 0.2f)
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

		if (input->IsKeyPressed(KEY_LSHIFT))
		{
			if (input->IsKeyHeld(KEY_LSHIFT))
			{
				for (int i = 0; i < bearTraps.size(); i++)
				{
					if (collision->BearTrapActivation(bearTraps.at(i)))
					{
						if (bearTraps.at(i)->GetState()->GetTrapState() == TrapState::TRAP_INACTIVE_STATE)
						{
							audioManager->playRepairLoop();
							if (bearTraps.at(i)->GetCurrentReloadTime() >= 2)
							{
								audioManager->playRepairComplete();
								bearTraps.at(i)->GetState()->SetTrapState(TrapState::TRAP_IDLE_STATE);
								bearTraps.at(i)->SetCurrentReloadTime(0);
								bearTraps.at(i)->SetisBeingReloaded(false);
							}
							else
							{

								bearTraps.at(i)->TickCurrReloadTime((float)*deltaTime);
								bearTraps.at(i)->SetisBeingReloaded(true);
							}


						}
					}
				}
				for (int i = 0; i < fireTraps.size(); i++)
				{
					if (collision->FireTrapActivation(fireTraps.at(i)))
					{

						if (fireTraps.at(i)->GetState()->GetTrapState() == TrapState::TRAP_INACTIVE_STATE)
						{
							audioManager->playRepairLoop();
								if (fireTraps.at(i)->GetCurrentReloadTime() >= 2)
								{
									audioManager->playRepairComplete();
									fireTraps.at(i)->GetState()->SetTrapState(TrapState::TRAP_IDLE_STATE);
									fireTraps.at(i)->SetCurrentReloadTime(0);
									fireTraps.at(i)->SetisBeingReloaded(false);

								}
								else
								{

									fireTraps.at(i)->TickCurrReloadTime((float)*deltaTime);
									fireTraps.at(i)->SetisBeingReloaded(true);
								}
						}
					}
				}
			}
		}
		else
		{
			audioManager->stopRepairLoop();
			currentTime = 0;
		}
		
		/*for (size_t i = 0; i < bearTraps.size(); i++)
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
		}*/

		if (moveKeysPressed > 0)
		{
			player->Move(directions, moveKeysPressed, deltaTime[0]);
		}
#pragma endregion

		if (input->IsKeyPressed(KEY_ESC) && timeSincePaused >0.2f)
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

void GameState::NewGame()
{
	Release();

	delete this->death;
	delete this->pause;
	delete this->player;
	delete this->room1;
	delete this->menu;
	delete this->gameUI;

	this->death = new MainDeathState();
	this->pause = new MainPausedState();
	this->player = new Player();
	this->input = Input::GetInstance();
	this->room1 = new Scene();
	this->collision = Collision::GetInstance();
	this->gameTimer = GameTimer::GetInstance();
	this->menu = new MenuState();
	this->gameUI = new GUI();

	Initialize(audioManager);
}