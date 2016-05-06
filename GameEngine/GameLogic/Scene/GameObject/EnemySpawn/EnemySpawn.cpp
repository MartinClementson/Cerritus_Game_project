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

void EnemySpawn::Initialize(XMFLOAT3 spawnPosition)
{
	this->spawnPosition = spawnPosition;
	waves.SetWave(currentWave);
	waves.WaveInformation();
	waveAmount = waves.GetWaveInformation();
	InitEnemy();
}

void EnemySpawn::Release()
{

}

void EnemySpawn::Update(double deltaTime)
{
	for (size_t i = 0; i < 2; i++)
	{
		if (!waveAmount == 0)
		{
			for (size_t i = 0; i < Alive.size(); i++)
			{

				if (collision->PlayerProxyEnemy(Alive.at(i)))
				{
					for (size_t j = 0; j < Alive.size(); j++)
					{
						Alive.at(j)->GetStateMachine()->
							SetActiveState(EnemyState::ENEMY_ATTACK_STATE);
					}
				}
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

					//waveAmount--;
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

					//waveAmount--;

				}
			}
			if (Alive.size() == 0)
			{
				spawnTimer += (float)deltaTime;
				if (!firstSpawn)
				{
					SpawnEnemy();
					spawnTimer = 0;
				}
				else if (spawnTimer >= 3 && firstSpawn)
				{
					

						RespawnEnemy();
						spawnTimer = 0;
						enemyWaveAmount++;

				}
			}
		}
		else 
		{
				waves.SetWave(currentWave += 1);
				waves.WaveInformation();
				waveAmount = waves.GetWaveInformation();
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
	firstSpawn = true;
	
	for(size_t i = 0; i < waveAmount ; i++)
	{
		if (!Queue.at(i)->isAlive)
		{

			float spawnX = spawnPosition.x + float(rand() % 15 + 5.0f);
			float spawnZ = spawnPosition.z + float(rand() % 50 + 5.0f);

			XMFLOAT3 spawn;
			spawn.x = spawnX;
			spawn.y = 0;
			spawn.z = spawnZ;
			
			Queue.at(i)->Spawn(spawn); //sets position and isAlive to TRUE
			Alive.push_back(Queue.at(i));
			Queue.erase(Queue.begin() + i);
			

			//done = true;
		}
		//i++;
	}
}

void EnemySpawn::RespawnEnemy()
{
	for (size_t i = 0; i< waveAmount; i++)
	{
		if (!Queue.at(i)->isAlive)
		{
			float spawnX = spawnPosition.x + float(rand() % 15 + 5.0f);
			float spawnZ = spawnPosition.z + float(rand() % 50 + 5.0f);

			XMFLOAT3 spawn;
			spawn.x = spawnX;
			spawn.y = 0;
			spawn.z = spawnZ;

			Queue.at(i)->Respawn(spawn); //sets position and isAlive to TRUE
			Alive.push_back(Queue.at(i));
			Queue.erase(Queue.begin() + i);

			//done = true;
		}
		//i++;
	}
}

void EnemySpawn::InitEnemy()
{
	/*waves.Initialize();

	int enemyAmount;
	enemyAmount = waves.GetWaveInformation();*/
	unsigned int waveAmount = 5;

	for (int i = 0; i < waveAmount; i++)
	{
		int spawnPointRandom = rand() % 4 + 1;

		if (spawnPointRandom == 1)
		{
			float spawnX = float(rand() % 15 + 5.0f);
			float spawnZ = float(rand() % 50 + 5.0f);

			XMFLOAT3 spawn;
			spawn.x = spawnX;
			spawn.y = 0;
			spawn.z = spawnZ;

			Queue.push_back( new Enemy(spawn) );
		}
		if (spawnPointRandom == 2)
		{
			float spawnX = float(rand() % 15 + 5.0f);
			float spawnZ = float(rand() % 50 + 5.0f);

			XMFLOAT3 spawn;
			spawn.x = spawnX;
			spawn.y = 0;
			spawn.z = spawnZ;

			Queue.push_back( new Enemy(spawn) );
		}
		if (spawnPointRandom == 3)
		{
			float spawnX = float(rand() % 15 + 5.0f);
			float spawnZ = float(rand() % 50 + 5.0f);

			XMFLOAT3 spawn;
			spawn.x = spawnX;
			spawn.y = 0;
			spawn.z = spawnZ;

			Queue.push_back(new Enemy(spawn));
		}
		if (spawnPointRandom == 4)
		{
			float spawnX = float(rand() % 15 + 5.0f);
			float spawnZ = float(rand() % 50 + 5.0f);

			XMFLOAT3 spawn;
			spawn.x = spawnX;
			spawn.y = 0;
			spawn.z = spawnZ;

			Queue.push_back(new Enemy(spawn));
		}
	}
	for(int i = 0; i < (int)Queue.size(); i++)
	{ 
		collision->AddEnemy(Queue.at(i));
	}
}

//void EnemySpawn::GetEnemyInfo(int info)
//{
//
//}

void EnemySpawn::Render()
{
	for (unsigned int i = 0; i < (int)Alive.size(); i++)
	{
		
			Alive.at(i)->Render();
	}
}
