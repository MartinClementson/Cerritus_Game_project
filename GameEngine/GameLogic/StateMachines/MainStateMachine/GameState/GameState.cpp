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

	index = 0;

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

		room1->Update(deltaTime);
		
		if (room1->toWin == true)
		{
			toWin = true;
		}

		size_t j = 0;
		while (j < room1->enemySpawn->Alive.size())
		{
			for (size_t p = 0; p < room1->enemySpawn->Alive.size(); p++)
			{
				if (room1->enemySpawn->Alive.at(p)->isAlive == true)
				{
					if (j == p || collision->PlayerDistanceCollision(
						room1->enemySpawn->Alive.at(p)))
					{
						room1->enemySpawn->Alive.at(p)->AIPattern(
							collision->GetPlayer(),
							deltaTime);
					}

					else if (collision->EnemyCollision(
						room1->enemySpawn->Alive.at(p),
						room1->enemySpawn->Alive.at(j)))
					{
						room1->enemySpawn->Alive.at(p)->EnemyWithEnemyCollision(
							room1->enemySpawn->Alive.at(p),
							room1->enemySpawn->Alive.at(j),
							deltaTime);
					}
				}
			}
			j++;
		}

		for (size_t i = 0; i < room1->WeaponUpgrades.size(); i++)
		{
			if (collision->WeaponPickupCollision(room1->WeaponUpgrades.at(i)))
			{
				if (room1->WeaponUpgrades.at(i)->GetPickupType() == PickupType::Weapon)
				{
					this->player->UpgradeWeapon();
					room1->WeaponUpgrades.at(i)->SetIsActive(false);
				}
				else if (room1->WeaponUpgrades.at(i)->GetPickupType() == PickupType::Heal)
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

		size_t i = 0; //kolla in denna efter du fixat renderingen
		while (i < player->projectileSystem->GetFiredProjectiles())
		{
			size_t j = 0;
			while (j <  room1->enemySpawn->Alive.size())
			{
				if (collision->ProjectileEnemyCollision(
					player->projectileSystem->
					projectiles[i],

					room1->enemySpawn->
					Alive.at(j))

					&& room1->enemySpawn->
					Alive.at(j)->isAlive == true)
				{
					room1->enemySpawn->Alive.at(j)->SetHealth(
						room1->enemySpawn->Alive.at(j)->GetHealth() - 10);
					player->projectileSystem->projectiles[i]->SetFired(false);
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
	XMFLOAT2 temp = input->GetMousePosition();

	if (death->isActive)
	{

	}
	else if (pause->isActive)
	{
		gameUI->setUI(UITextures::PAUSE);

		XMFLOAT2 mousePos = InputHandler::GetInstance()->GetMousePosition();

		float vx = ((2.0f * mousePos.x) / (float)WIN_HEIGHT - 1.0f);
		float vy = ((2.0f * -mousePos.y) / (float)WIN_WIDTH + 1.0f);

		XMFLOAT2 Maxexit = { 493.0f ,460.0f };
		XMFLOAT2 Minexit = { 792.0f,511.0f };

		float Maxex = ((2.0f * Maxexit.x) / (float)WIN_HEIGHT - 1.0f);
		float Maxey = ((2.0f * -Maxexit.y) / (float)WIN_WIDTH + 1.0f);
		float Minex = ((2.0f * Minexit.x) / (float)WIN_HEIGHT - 1.0f);
		float Miney = ((2.0f * -Minexit.y) / (float)WIN_WIDTH + 1.0f);


		XMFLOAT2 MaxResumeGame = { 490.0f,216.0f };
		XMFLOAT2 MinResumeGame = { 788.0f,269.0f };

		float Maxnx = ((2.0f * MaxResumeGame.x) / (float)WIN_HEIGHT - 1.0f);
		float Maxny = ((2.0f * -MaxResumeGame.y) / (float)WIN_WIDTH + 1.0f);
		float Minnx = ((2.0f * MinResumeGame.x) / (float)WIN_HEIGHT - 1.0f);
		float Minny = ((2.0f * -MinResumeGame.y) / (float)WIN_WIDTH + 1.0f);

		XMFLOAT2 MaxRestart = { 490.0f,333.0f };
		XMFLOAT2 MinRestart = { 787.0f,387.0f };

		float Maxcx = ((2.0f * MaxRestart.x) / (float)WIN_HEIGHT - 1.0f);
		float Maxcy = ((2.0f * -MaxRestart.y) / (float)WIN_WIDTH + 1.0f);
		float Mincx = ((2.0f * MinRestart.x) / (float)WIN_HEIGHT - 1.0f);
		float Mincy = ((2.0f * -MinRestart.y) / (float)WIN_WIDTH + 1.0f);

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

			}
		}
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