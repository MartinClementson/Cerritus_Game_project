#include "GameState.h"



GameState::GameState()
{
	this->death = new MainDeathState();
	this->pause = new MainPausedState();
	this->player = new Player();
	this->menu = new MenuState();
	this->input = Input::GetInstance();
	this->room1 = new Scene();
	this->collision = Collision::GetInstance();
	this->gameTimer = GameTimer::GetInstance();
	this->gameUI = new GUI();
}


GameState::~GameState()
{
	delete this->death;
	delete this->pause;
	delete this->player;
	delete this->room1;
	delete this->gameUI;
	delete this->menu;
}

void GameState::Initialize()
{
	input->Initialize();
	player->Initialize();
	death->Initialize();
	pause->Initialize();
	menu->Initialize();
	menu->isActive = false;
	death->isActive = false;
	pause->isActive = false;
	gameUI->Initialize();
	isPlayerDead = false;
	toMenu = false;
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
	gameUI->Release();
	menu->Release();
}

void GameState::Update(double deltaTime)
{

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


	room1->Update(deltaTime);
	int i = 0;


	//while(i < (int)player->projectileSystem->projectiles.size())
	
	while( i < player->projectileSystem->projectiles.size())

	{


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
						room1->enemySpawns.at(k)->Alive.at(j)->SetHealth(
							room1->enemySpawns.at(k)->Alive.at(j)->GetHealth() - 10);
					}


					j++;
				}
			}
			i++;
		}
	}
	else if (pause->isActive)
	{
		XMFLOAT2 mousePos = InputHandler::GetInstance()->GetMousePosition();

		float vx = ((2.0f * mousePos.x) / (float)WIN_HEIGHT - 1.0f);
		float vy = ((2.0f * -mousePos.y) / (float)WIN_WIDTH + 1.0f);
		//resumeButton
		XMFLOAT2 MaxResume = { 496.0f,183.0f };
		XMFLOAT2 MinResume = { 714.0f,243.0f };

		float MaxRx = ((2.0f * MaxResume.x) / (float)WIN_HEIGHT - 1.0f);
		float MaxRy = ((2.0f * -MaxResume.y) / (float)WIN_WIDTH + 1.0f);
		float MinRx = ((2.0f * MinResume.x) / (float)WIN_HEIGHT - 1.0f);
		float MinRy = ((2.0f * -MinResume.y) / (float)WIN_WIDTH + 1.0f);

		// RestartButton
		XMFLOAT2 MaxRestart = {496.0f,299.0f};
		XMFLOAT2 MinRestart = {714.0f,358.0f};

		float Maxrex = ((2.0f * MaxRestart.x) / (float)WIN_HEIGHT - 1.0f);
		float Maxrey = ((2.0f * -MaxRestart.y) / (float)WIN_WIDTH + 1.0f);
		float Minrex = ((2.0f * MinRestart.x) / (float)WIN_HEIGHT - 1.0f);
		float Minrey = ((2.0f * -MinRestart.y) / (float)WIN_WIDTH + 1.0f);

		//ExitButton = to menu
		XMFLOAT2 MaxExit = {496.0f,410.0f};
		XMFLOAT2 MinExit = {714.0f,470.0f};
		float Maxex = ((2.0f * MaxExit.x) / (float)WIN_HEIGHT - 1.0f);
		float Maxey = ((2.0f * -MaxExit.y) / (float)WIN_WIDTH + 1.0f);
		float Minex = ((2.0f * MinExit.x) / (float)WIN_HEIGHT - 1.0f);
		float Miney = ((2.0f * -MinExit.y) / (float)WIN_WIDTH + 1.0f);

		if (vx > MaxRx && vy < MaxRy && vx < MinRx && vy > MinRy && timeSincePaused > 0.2f)
		{
			
			//gameUI->setUI(UITextures::TEXTATLAS);

			if (input->isMouseClicked(MOUSE_LEFT))
			{
				pause->isActive = false;
				timeSincePaused = 0.0f;
				gameUI->setUI(UITextures::HUD);
			}
		}
		else if (vx > Maxex && vy < Maxey && vx < Minex && vy > Miney && timeSincePaused > 0.2f)
		{
		//	gameUI->setPos()
			//gameUI->setUI(UITextures::TEXTATLAS);
			if(input->isMouseClicked(MOUSE_LEFT))
			{
				toMenu = true;
				menu->isActive = true;
				timeSincePaused = 0.0f;
			}
					}
		else if (vx > Maxrex && vy < Maxrey && vx < Minrex && vy > Minrey && timeSincePaused > 0.2f)
		{
			//gameUI->setUI(UITextures::TEXTATLAS);
			if (input->isMouseClicked(MOUSE_LEFT))
			{

			}
		}
		else
		{
			gameUI->setUI(UITextures::PAUSE);
		}
	}
	gameUI->Update(deltaTime);
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
		//XMFLOAT2 mousePos = InputHandler::GetInstance()->GetMousePosition();

		//float vx = ((2.0f * mousePos.x) / (float)WIN_HEIGHT - 1.0f);
		//float vy = ((2.0f * -mousePos.y) / (float)WIN_WIDTH + 1.0f);
		////resumeButton
		//XMFLOAT2 MaxResume = { 496.0f,183.0f };
		//XMFLOAT2 MinResume = { 714.0f,243.0f };

		//float MaxRx = ((2.0f * MaxResume.x) / (float)WIN_HEIGHT - 1.0f);
		//float MaxRy = ((2.0f * -MaxResume.y) / (float)WIN_WIDTH + 1.0f);
		//float MinRx = ((2.0f * MinResume.x) / (float)WIN_HEIGHT - 1.0f);
		//float MinRy = ((2.0f * -MinResume.y) / (float)WIN_WIDTH + 1.0f);

		//// RestartButton
		//XMFLOAT2 MaxRestart = {496.0f,299.0f};
		//XMFLOAT2 MinRestart = {714.0f,358.0f};

		//float Maxrex = ((2.0f * MaxRestart.x) / (float)WIN_HEIGHT - 1.0f);
		//float Maxrey = ((2.0f * -MaxRestart.y) / (float)WIN_WIDTH + 1.0f);
		//float Minrex = ((2.0f * MinRestart.x) / (float)WIN_HEIGHT - 1.0f);
		//float Minrey = ((2.0f * -MinRestart.y) / (float)WIN_WIDTH + 1.0f);

		////ExitButton = to menu
		//XMFLOAT2 MaxExit = {496.0f,410.0f};
		//XMFLOAT2 MinExit = {714.0f,470.0f};
		//float Maxex = ((2.0f * MaxExit.x) / (float)WIN_HEIGHT - 1.0f);
		//float Maxey = ((2.0f * -MaxExit.y) / (float)WIN_WIDTH + 1.0f);
		//float Minex = ((2.0f * MinExit.x) / (float)WIN_HEIGHT - 1.0f);
		//float Miney = ((2.0f * -MinExit.y) / (float)WIN_WIDTH + 1.0f);

		//if (vx > MaxRx && vy < MaxRy && vx < MinRx && vy > MinRy)
		//{
		//	
		//	gameUI->setUI(UITextures::RESUMEPAUSE);

		//	if (input->isMouseClicked(MOUSE_LEFT))
		//	{
		//		pause->isActive = false;
		//		gameUI->setUI(UITextures::HUD);
		//	}
		//}
		//else if (vx > Maxex && vy < Maxey && vx < Minex && vy > Miney)
		//{

		//	gameUI->setUI(UITextures::EXITPAUSE);
		//	if(input->isMouseClicked(MOUSE_LEFT))
		//	{
		//		toMenu = true;
		//		menu->isActive = true;
		//		
		//	}
		//}
		//else if (vx > Maxrex && vy < Maxrey && vx < Minrex && vy > Minrey)
		//{
		//	gameUI->setUI(UITextures::RESTARTPAUSE);
		//	if (input->isMouseClicked(MOUSE_LEFT))
		//	{

		//	}
		//}
		
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
		if (input->IsKeyPressed(KEY_P))
		{
			toMenu = true;
			menu->isActive = true;
			//gameUI->setUI(UITextures::MENU);
			//UITextures::MENU;
		}

		if (input->IsKeyPressed(KEY_ENTER) && timeSincePaused >0.2f)
		{
			pause->isActive = true;
			timeSincePaused = 0.0f;
			gameUI->setUI(UITextures::PAUSE);
			InputHandler::GetInstance()->GetMousePosition();
			

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