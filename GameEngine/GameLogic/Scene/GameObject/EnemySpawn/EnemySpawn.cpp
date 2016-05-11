#include "EnemySpawn.h"

EnemySpawn::EnemySpawn()
{
	this->collision = Collision::GetInstance();
	this->firstSpawn = false;
}

EnemySpawn::~EnemySpawn()
{
	for (size_t i = 0; i < Queue.size(); i++)
	{
			delete Queue.at(i);
	}

	for (size_t i = 0; i < Alive.size(); i++)
	{
		delete Alive.at(i);
	}
}

void EnemySpawn::Initialize()
{
	waves.SetWaveGroup(currentWave);
	waves.WaveInformation();
	waveAmount = waves.GetWaveInformation();
	InitEnemy();
}

void EnemySpawn::Release()
{

}

void EnemySpawn::Update(double deltaTime)
{
		if (!waveAmount == 0)
		{
			for (size_t j = 0; j < Alive.size(); j++)
			{
				Alive.at(j)->GetStateMachine()->
					SetActiveState(EnemyState::ENEMY_ATTACK_STATE);
			}	
			
			for (size_t i = 0; i < Alive.size(); i++)
			{

				Alive.at(i)->Update(deltaTime);

				if (Alive.at(i)->GetHealth() <= 0 &&
					Alive.at(i)->GetStateMachine()->
					GetActiveState() == EnemyState::ENEMY_ATTACK_STATE)
				{
					Player* player;
					player = collision->GetPlayer();
					player->SetPoints(player->GetPoints() + (10.0f*player->GetMulti()));
					player->SetMulti(player->GetMulti() + 0.1f);

					Alive.at(i)->isAlive = false;
					Alive.at(i)->SetHealth(100.0f);
					Alive.at(i)->GetStateMachine()->
						SetActiveState(EnemyState::ENEMY_DEATH_STATE);

					Queue.push_back(Alive.at(i));

					Alive.erase(Alive.begin() + i);

					waveAmount--;


				}
				else if (Alive.at(i)->GetHealth() <= 0 &&
					Alive.at(i)->GetStateMachine()->
					GetActiveState() == EnemyState::ENEMY_IDLE_STATE)
				{
					Player* player;
					player = collision->GetPlayer();
					player->SetPoints(player->GetPoints() - 10.0f);
					player->SetMulti(1);

					Alive.at(i)->isAlive = false;
					Alive.at(i)->SetHealth(100.0f);
					Alive.at(i)->GetStateMachine()->
						SetActiveState(EnemyState::ENEMY_DEATH_STATE);

					Queue.push_back(Alive.at(i));
					Alive.erase(Alive.begin() + i);

					waveAmount--;

				}
			}
			if (Alive.size() == 0)
			{
				//spawnTimer += (float)deltaTime;
				if (!firstSpawn)
				{
					SpawnEnemy();
					//spawnTimer = 0;
				}
				else/* if (spawnTimer >= 3 && firstSpawn)*/
				{
						RespawnEnemy();
						//spawnTimer = 0;
				}
			}
		}
		else 
		{
				waves.SetWaveGroup(currentWave += 1);
				waves.WaveInformation();
				waveAmount = waves.GetWaveInformation();
				
				if (waveAmount == 0)
				{
					waveTimer += deltaTime;
					if (waveTimer >= 5)
					{
						waves.SetWaveGroup(currentWave = 1);
					}
				}
		}
		for (int i = 0; i < (int)Alive.size(); i++)
		{
			if (Alive.at(i)->isAlive == true)
			{
				
				if (collision->PlayerCollision(Alive.at(i)))
				{
					Player* player;
					player = collision->GetPlayer();

				}
			}
		}	
}

void EnemySpawn::SpawnEnemy()
{
	intSpawn = rand() % 4 + 1;

	firstSpawn = true;
	
	for(size_t i = 0; i < Queue.size(); i++)
	{
		if (!Queue.at(i)->isAlive)
		{
			if (intSpawn == 5)
			{
				intSpawn = 1;

				waves.SpawnPositions(intSpawn);

				spawn = waves.GetSpawnPositions();

				Queue.at(i)->Spawn(spawn); //sets position and isAlive to TRUE
				Alive.push_back(Queue.at(i));
				Queue.erase(Queue.begin() + i);

				intSpawn++;

			}
			else 
			{
				waves.SpawnPositions(intSpawn);

				spawn = waves.GetSpawnPositions();

				Queue.at(i)->Spawn(spawn); //sets position and isAlive to TRUE
				Alive.push_back(Queue.at(i));
				Queue.erase(Queue.begin() + i);
				
				intSpawn++;
			}		

		}
	}
}

void EnemySpawn::RespawnEnemy()
{
	intSpawn = rand() % 4 + 1;

	for (size_t i = 0; i < Queue.size(); i++)
	{
		if (!Queue.at(i)->isAlive)
		{
			if (intSpawn == 5)
			{
				intSpawn = 1;

				waves.SpawnPositions(intSpawn);

				spawn = waves.GetSpawnPositions();

				Queue.at(i)->Respawn(spawn); //sets position and isAlive to TRUE
				Alive.push_back(Queue.at(i));
				Queue.erase(Queue.begin() + i);

				intSpawn++;
			}

			else
			{
				waves.SpawnPositions(intSpawn);

				spawn = waves.GetSpawnPositions();

				Queue.at(i)->Respawn(spawn); //sets position and isAlive to TRUE
				Alive.push_back(Queue.at(i));
				Queue.erase(Queue.begin() + i);

				intSpawn++;
			}
		}
	}
}

void EnemySpawn::InitEnemy()
{
	/*waves.Initialize();

	int enemyAmount;
	enemyAmount = waves.GetWaveInformation();*/
	unsigned int amount = 22;

	for (int i = 0; i < amount; i++)
	{
		int spawnPointRandom = rand() % 4 + 1;

		if (spawnPointRandom == 1)
		{
			XMFLOAT3 spawn;
	
			Queue.push_back(new Enemy(spawn));
		}
		if (spawnPointRandom == 2)
		{
			XMFLOAT3 spawn;

			Queue.push_back(new Enemy(spawn));
		}
		if (spawnPointRandom == 3)
		{

			XMFLOAT3 spawn;

			Queue.push_back(new Enemy(spawn));
		}
		if (spawnPointRandom == 4)
		{
			XMFLOAT3 spawn;

			Queue.push_back(new Enemy(spawn));
		}
	}
	for(int i = 0; i < (int)Queue.size(); i++)
	{ 
		collision->AddEnemy(Queue.at(i));
	}
}

void EnemySpawn::Render()
{
	for (unsigned int i = 0; i < (int)Alive.size(); i++)
	{
		Alive.at(i)->Render();
	}
}
