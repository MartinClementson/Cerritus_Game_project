#include "EnemySpawn.h"

EnemySpawn::EnemySpawn()
{
	this->collision = Collision::GetInstance();
	this->firstSpawn = false;
	this->playWave = true;
}

EnemySpawn::~EnemySpawn()
{
	for (size_t i = 0; i < Alive.size(); i++)
	{
		delete Alive.at(i);
	}
}

void EnemySpawn::Initialize(AudioManager* audioManager)
{
	this->audioManager = audioManager;
	graphics = Graphics::GetInstance();
	currentWave = 1;
	waves.SetWaveGroup(currentWave);
	waves.WaveInformation();
	waveAmount = waves.GetWaveInformation();

	WaveComplete.UIobject = UITextures::WAVECOMPLETE;

	InitEnemy();
}

void EnemySpawn::Release()
{

}

void EnemySpawn::Update(double deltaTime)
{
		/*for (size_t j = 0; j < Alive.size(); j++)
		{
			Alive.at(j)->GetStateMachine()->
				SetActiveState(EnemyState::ENEMY_ATTACK_STATE);
		}*/

		for (int i = 0; i < Alive.size(); i++)
		{
			Alive.at(i)->Update(deltaTime);

			if (Alive.at(i)->GetHealth() <= 0)
			{
				Player* player;
				player = collision->GetPlayer();
				player->SetPoints(player->GetPoints() + (10.0f*player->GetMulti()));
				player->SetMulti(player->GetMulti() + 0.1f);

				Alive.at(i)->isAlive = false;
				Alive.at(i)->SetHealth(100.0f);
				Alive.at(i)->GetStateMachine()->
					SetActiveState(EnemyState::ENEMY_DEATH_STATE);
				audioManager->playEDeathSound();
				waveAmount--;

				/*if (waveAmount != 0)
				{
					RespawnEnemy(i);
				}*/
				//else
				//{
				//	/*while (waveTimer < 200)
				//	{
				//		waveTimer += deltaTime;
				//	}*/

				//	waves.SetWaveGroup(currentWave += 1);
				//	waves.WaveInformation();
				//	waveAmount = waves.GetWaveInformation();

				//	if (waveAmount == 0)
				//	{
				//		win = true;
				//		//waves.SetWinCondition(win);
				//	}
				//	SpawnEnemy(waveAmount);
				//}
			}
			//else if (Alive.at(i)->GetHealth() <= 0 &&
			//	Alive.at(i)->GetStateMachine()->
			//	GetActiveState() == EnemyState::ENEMY_HEAL_STATE
			//	)
			//{
			//	Player* player;
			//	player = collision->GetPlayer();
			//	player->SetPoints(player->GetPoints() + (10.0f*player->GetMulti()));
			//	player->SetMulti(player->GetMulti() + 0.1f);

			//	Alive.at(i)->isAlive = false;
			//	Alive.at(i)->SetHealth(100.0f);
			//	Alive.at(i)->GetStateMachine()->
			//		SetActiveState(EnemyState::ENEMY_DEATH_STATE);

			//	waveAmount--;

			//	if (waveAmount != 0)
			//	{
			//		RespawnEnemy(i);
			//	}
			//	/*else
			//	{
			//		waves.SetWaveGroup(currentWave += 1);
			//		waves.WaveInformation();
			//		waveAmount = waves.GetWaveInformation();

			//		SpawnEnemy(waveAmount);
			//	}*/
			//}
		}

		if (!firstSpawn)
		{
			if (waves.GetWaveTimer() <= 0)
			{
				SpawnEnemy(waveAmount);
			}
			else
			{
				graphics->QueueRender(&WaveComplete);
				if (waves.GetWaveTimer() <= 6 && playWave)
				{
					audioManager->playNewWave();
					playWave = false;
				}
			}
		}

		for (int i = 0; i < (int)Alive.size(); i++)
		{
			if (Alive.at(i)->isAlive == true)
			{
				collision->PlayerCollision(Alive.at(i));
				if (!collision->SceneColIn(deltaTime, Alive.at(i))) //change this
				{
					Alive.at(i)->position.x = Alive.at(i)->position.x;
					Alive.at(i)->position.z = Alive.at(i)->position.z;
				}
				if (collision->SceneColIn(deltaTime, Alive.at(i)))
				{
					Alive.at(i)->position.x = Alive.at(i)->position.x;
					Alive.at(i)->position.z = Alive.at(i)->position.z;
				}
			}
		}
	if (waveAmount == 0)
	{
			/*while (waveTimer < 200)
			{
			waveTimer += deltaTime;
			}*/

			waves.SetWaveGroup(currentWave += 1);
			waves.WaveInformation();
			waveAmount = waves.GetWaveInformation();
			pickupRespawn = true;
			playWave = true;
			if (waveAmount == 0)
			{
				win = true;
				//waves.SetWinCondition(win);
			}
			
		
			else
				firstSpawn = false;
	}
	waves.Update(deltaTime);
}	

void EnemySpawn::SpawnEnemy(int waveAmount)
{
	float x = 0;

	firstSpawn = true;

	for (int i = 0; i < waveAmount; i++)
	{
		intSpawn = rand() % 4 + 1;

			if (intSpawn == 1)
			{
				waves.SetSpawnPosAdd(x);
				waves.SpawnPositions(1);
				spawn = waves.GetSpawnPositions();
			}
			else if (intSpawn == 2)
			{
				waves.SetSpawnPosAdd(x);
				waves.SpawnPositions(2);
				spawn = waves.GetSpawnPositions();

			}
			else if (intSpawn == 3)
			{
				waves.SetSpawnPosAdd(x);
				waves.SpawnPositions(3);
				spawn = waves.GetSpawnPositions();
			}
			else if (intSpawn == 4)
			{
				waves.SetSpawnPosAdd(x);
				waves.SpawnPositions(4);
				spawn = waves.GetSpawnPositions();
			}

			x += 1;

			Alive.at(i)->Spawn(spawn);

	}

}

void EnemySpawn::RespawnEnemy(int i)
{
	float x = 0;
	intSpawn = rand() % 4 + 1;

	if (intSpawn == 1)
	{
		waves.SetSpawnPosAdd(x);
		waves.SpawnPositions(1);
		spawn = waves.GetSpawnPositions();
	}
	else if (intSpawn == 2)
	{
		waves.SetSpawnPosAdd(x);
		waves.SpawnPositions(2);
		spawn = waves.GetSpawnPositions();

	}
	else if (intSpawn == 3)
	{
		waves.SetSpawnPosAdd(x);
		waves.SpawnPositions(3);
		spawn = waves.GetSpawnPositions();
	}
	else if (intSpawn == 4)
	{
		waves.SetSpawnPosAdd(x);
		waves.SpawnPositions(4);
		spawn = waves.GetSpawnPositions();
	}
	x += 5;

	Alive.at(i)->Respawn(spawn);
}

void EnemySpawn::InitEnemy()
{
	unsigned int amount = 80;
	float b = 0;

	for (size_t i = 0; i < amount; i++)
	{
		if(i % 10 || i == 0)
		{
			int spawnPointRandom = rand() % 4 + 1;

			if (spawnPointRandom == 1)
			{
				waves.SetSpawnPosAdd(b);
				waves.SpawnPositions(1);
				spawn = waves.GetSpawnPositions();

				fast = false;
			}
			else if (spawnPointRandom == 2)
			{

				waves.SetSpawnPosAdd(b);
				waves.SpawnPositions(2);
				spawn = waves.GetSpawnPositions();

				fast = true;

			}
			else if (spawnPointRandom == 3)
			{
				waves.SetSpawnPosAdd(b);
				waves.SpawnPositions(3);
				spawn = waves.GetSpawnPositions();

				fast = false;

			}
			else if (spawnPointRandom == 4)
			{
				waves.SetSpawnPosAdd(b);
				waves.SpawnPositions(4);
				spawn = waves.GetSpawnPositions();

				fast = true;

			}



			b += 5;

			Alive.push_back(new Enemy(spawn, fast));
		}
		else
		{
			waves.SetSpawnPosAdd(b);
			waves.SpawnPositions(1);
			spawn = waves.GetSpawnPositions();

			Alive.push_back(new Healer(spawn));
		}
		
	}
}

void EnemySpawn::Render()
{
	for (size_t i = 0; i < Alive.size(); i++)
	{
		if (Alive.at(i)->isAlive == true)
		{
			Alive.at(i)->Render();
		}
	}
}
