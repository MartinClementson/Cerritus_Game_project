#include "EnemySpawn.h"



EnemySpawn::EnemySpawn()
{
	this->collision = Collision::GetInstance();
	this->firstSpawn = false;
	nrOfAliveEnemies = 0;
	this->playWave = true;
}

EnemySpawn::~EnemySpawn()
{
	for (size_t i = 0; i < 100; i++)
	{
		delete Alive[i];
	}
}

void EnemySpawn::Initialize(AudioManager* audioManager)
{
	this->audioManager = audioManager;
	graphics = Graphics::GetInstance();
	currentWave = 1;
	waves.SetWaveGroup(currentWave);
	waves.WaveInformation();
	nrOfAliveEnemies = waves.GetWaveInformation();

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

		for (int i = 0; i < nrOfAliveEnemies; i++)
		{
			Alive[i]->Update(deltaTime);

			if (Alive[i]->GetHealth() <= 0)
			{
				Player* player;
				player = collision->GetPlayer();
				player->SetPoints(player->GetPoints() + (10.0f*player->GetMulti()));
				player->SetMulti(player->GetMulti() + 0.1f);
				audioManager->playEDeathSound();
				killEnemy(i);
				//waveAmount--;
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
				SpawnEnemy(nrOfAliveEnemies);
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

		for (int i = 0; i < nrOfAliveEnemies; i++)
		{
			if (Alive[i]->isAlive == true)
			{
				collision->PlayerCollision(Alive[i]);
				if (!collision->SceneColIn(deltaTime, Alive[i])) //change this
				{
					Alive[i]->position.x = Alive[i]->position.x;
					Alive[i]->position.z = Alive[i]->position.z;
				}
				if (collision->SceneColIn(deltaTime, Alive[i]))
				{
					Alive[i]->position.x = Alive[i]->position.x;
					Alive[i]->position.z = Alive[i]->position.z;
				}
			}
		}
	if (nrOfAliveEnemies == 0)
	{
			/*while (waveTimer < 200)
			{
			waveTimer += deltaTime;
			}*/

			waves.SetWaveGroup(currentWave += 1);
			waves.WaveInformation();
			nrOfAliveEnemies = waves.GetWaveInformation();

			
			//waveAmount = waves.GetWaveInformation();
			pickupRespawn = true;
			playWave = true;
			if (nrOfAliveEnemies == 0)
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

	//nrOfAliveEnemies = waveAmount;

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

			Alive[i]->Spawn(spawn);

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
	x += 1;

	Alive[i]->Respawn(spawn);
}

void EnemySpawn::InitEnemy()
{
	unsigned int amount = 80;
	float b = 0;

	for (size_t i = 0; i < 100; i++)
	{
		//nrOfAliveEnemies++;
		int spawnPointRandom = rand() % 5 + 1;

		/*if (spawnPointRandom == 1)
		{
			waves.SetSpawnPosAdd(b);
			waves.SpawnPositions(1);
			spawn = waves.GetSpawnPositions();
			
			fast = false;
			Alive[i] = (new Enemy(spawn, fast));
		}*/
		if (i % 10 || i == 0)
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

			//Alive.push_back(new Enemy(spawn, fast));
			Alive[i] = (new Enemy(spawn, fast));
		}
		else
		{
			waves.SetSpawnPosAdd(b);
			waves.SpawnPositions(1);
			spawn = waves.GetSpawnPositions();

			Alive[i] = (new Healer(spawn));
		}

		b += 1;

		Alive[i]->Initialize();

		/*for (int i = 0; i < nrOfAliveEnemies; i++)
		{
			if (Alive[i]->isAlive == true)
			{
				collision->AddEnemy(Alive[i]);
			}
		}*/
	}
}

void EnemySpawn::Render()
{
	for (size_t i = 0; i < nrOfAliveEnemies; i++)
	{
		if (Alive[i]->isAlive == true)
		{
			Alive[i]->Render();
		}
	}
}

void EnemySpawn::killEnemy(int index)
{
	Alive[index]->isAlive = false;
	Alive[index]->SetHealth(100.0f);
	Alive[index]->GetStateMachine()->
		SetActiveState(EnemyState::ENEMY_DEATH_STATE);

	nrOfAliveEnemies--;

	//swapping
	EnemyBase* temp;
	temp = Alive[index];
	Alive[index] = Alive[nrOfAliveEnemies];
	Alive[nrOfAliveEnemies] = temp;
}