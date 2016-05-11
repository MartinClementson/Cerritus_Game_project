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
	currentWave = 1;
	waves->SetWaveGroup(currentWave);
	waves->WaveInformation();
	waveAmount = waves->GetWaveInformation();
	InitEnemy();
}

void EnemySpawn::Release()
{

}

void EnemySpawn::Update(double deltaTime)
{
		if (waveAmount != 0)
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
				if (!firstSpawn)
				{
					SpawnEnemy();
				}
			}
		}

		else 
		{
				waves->SetWaveGroup(currentWave += 1);
				waves->WaveInformation();
				waveAmount = waves->GetWaveInformation();

				RespawnEnemy();

				if (waveAmount == 0)
				{
					waveTimer += deltaTime;
					if (waveTimer >= 5)
					{
						waves->SetWaveGroup(currentWave = 1);
					}
				}
		}
		for (size_t i = 0; i < Alive.size(); i++)
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

	for (int i = 0; i < waveAmount; i++)
	{
		if (!Queue.at(i)->isAlive)
		{
			intSpawn = rand() % 4 + 1;

			waves->SpawnPositions(intSpawn);

			spawnPosInfo;
			spawnPosInfo = waves->GetSpawnPositions();

			Queue.at(i)->Spawn(spawnPosInfo); //sets position and isAlive to TRUE
			Alive.push_back(Queue.at(i));
			Queue.erase(Queue.begin() + i);

			//done = true;
		}
		//i++;
	}
}

void EnemySpawn::RespawnEnemy()
{
	for (int i = 0; i < waveAmount; i++)
	{
		if (!Queue.at(i)->isAlive)
		{
			intSpawn = rand() % 4 + 1;

			waves->SpawnPositions(intSpawn);

			spawn;
			spawn = waves->GetSpawnPositions();

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
	unsigned int amount = 25;

	for (int i = 0; i < amount; i++)
	{
			spawn = { -70.0f, 0.0f, -40.0f };
	
			Queue.push_back(new Enemy(spawn));	
	}
	for(int i = 0; i < Queue.size(); i++)
	{ 
		collision->AddEnemy(Queue.at(i));
	}
}

void EnemySpawn::Render()
{
	for (size_t i = 0; i < Alive.size(); i++)
	{
		Alive.at(i)->Render();
	}
}
