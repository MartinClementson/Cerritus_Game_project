#include "EnemySpawn.h"

EnemySpawn::EnemySpawn()
{
	this->collision = Collision::GetInstance();
	this->firstSpawn = false;
}

EnemySpawn::~EnemySpawn()
{
	/*for (size_t i = 0; i < Queue.size(); i++)
	{
		delete Queue.at(i);
	}
*/
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

				Alive.at(i)->isAlive = false;

				waveAmount--;

				if (waveAmount != 0)
				{
					RespawnEnemy(i);
				}
				else
				{
					waves.SetWaveGroup(currentWave += 1);
					waves.WaveInformation();
					waveAmount = waves.GetWaveInformation();

					SpawnEnemy(waveAmount);
				}
			}
		}

	if (!firstSpawn)
	{
		SpawnEnemy(waveAmount);
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

void EnemySpawn::SpawnEnemy(int waveAmount)
{
	float x = 0;

	firstSpawn = true;
	
	for(size_t i = 0; i < waveAmount; i++)
	{
			intSpawn = rand() % 4 + 1;

			if (intSpawn == 1)
			{
				waves.SetSpawnPosAdd(x);
				waves.SpawnPositions(1);
				spawn = waves.GetSpawnPositions();
			}
			if (intSpawn == 2)
			{
				waves.SetSpawnPosAdd(x);
				waves.SpawnPositions(2);
				spawn = waves.GetSpawnPositions();
			}
			if (intSpawn == 3)
			{
				waves.SetSpawnPosAdd(x);
				waves.SpawnPositions(3);
				spawn = waves.GetSpawnPositions();
			}
			if (intSpawn == 4)
			{
				waves.SetSpawnPosAdd(x);
				waves.SpawnPositions(4);
				spawn = waves.GetSpawnPositions();
			}
			x += 5;
			
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
	if (intSpawn == 2)
	{
		waves.SetSpawnPosAdd(x);
		waves.SpawnPositions(2);
		spawn = waves.GetSpawnPositions();
	}
	if (intSpawn == 3)
	{
		waves.SetSpawnPosAdd(x);
		waves.SpawnPositions(3);
		spawn = waves.GetSpawnPositions();
	}
	if (intSpawn == 4)
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
	/*waves.Initialize();

	int enemyAmount;
	enemyAmount = waves.GetWaveInformation();*/
	unsigned int amount = 32;
	float b = 0;

	for (int i = 0; i < amount; i++)
	{
		intSpawn = rand() % 4 + 1;

		if (intSpawn == 1)
		{
			waves.SetSpawnPosAdd(b);
			waves.SpawnPositions(1);
			spawn = waves.GetSpawnPositions();
		}
		if (intSpawn == 2)
		{
			waves.SetSpawnPosAdd(b);
			waves.SpawnPositions(2);
			spawn = waves.GetSpawnPositions();
		}
		if (intSpawn == 3)
		{
			waves.SetSpawnPosAdd(b);
			waves.SpawnPositions(3);
			spawn = waves.GetSpawnPositions();
		}
		if (intSpawn == 4)
		{
			waves.SetSpawnPosAdd(b);
			waves.SpawnPositions(4);
			spawn = waves.GetSpawnPositions();
		}
		

		b += 5;

		//Queue.push_back(new Enemy(spawn));
		Alive.push_back(new Enemy(spawn));

	}
	for(int i = 0; i < (int)Alive.size(); i++)
	{ 
		if (Alive.at(i)->isAlive == true)
		{
			collision->AddEnemy(Alive.at(i));
		}
	}
}

void EnemySpawn::Render()
{
	for (unsigned int i = 0; i < (int)Alive.size(); i++)
	{
		if (Alive.at(i)->isAlive == true)
		{
			Alive.at(i)->Render();
		}
	}
}
