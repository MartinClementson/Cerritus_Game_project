#include "EnemySpawn.h"



EnemySpawn::EnemySpawn()
{
	
}

EnemySpawn::~EnemySpawn()
{
	for (int i = 0; i < Queue.size(); i ++)
	{
		delete Queue.at(i);
	}

	for (int i = 0; i < Alive.size(); i++)
	{
		delete Alive.at(i);
	}
}
void EnemySpawn::Initialize()
{
	InitEnemy();
}
void EnemySpawn::Release()
{

}
void EnemySpawn::Update(double deltaTime)
{
	if (Alive.size() <= 20)
	{
		SpawnEnemy();
	}
}

void EnemySpawn::SpawnEnemy()
{
	if (Queue.size() > 0)
	{
		Alive.push_back(Queue.at(0));
		Queue.erase(Queue.begin());
	}
}

void EnemySpawn::InitEnemy()
{
	unsigned int waveAmount = 20;

	for (int i = 1; i < waveAmount; i++)
	{
		int spawnPointRandom = rand() % 4 + 1;

		if (spawnPointRandom = 1)
		{
			float spawnX = rand() % 20 + 1.0f;
			float spawnZ = rand() % 20 + 1.0f;

			XMFLOAT3 spawn;
			spawn.x = spawnX;
			spawn.y = 0;
			spawn.z = spawnZ;

			Queue.push_back( new Enemy(spawn) );
		}
		if (spawnPointRandom = 2)
		{
			float spawnX = rand() % 40 + 5.0f;
			float spawnZ = rand() % 40 + 5.0f;

			XMFLOAT3 spawn;
			spawn.x = spawnX;
			spawn.y = 0;
			spawn.z = spawnZ;

			Queue.push_back( new Enemy(spawn) );
		}
		if (spawnPointRandom = 3)
		{
			float spawnX = rand() % -20 + -10.0f;
			float spawnZ = rand() % -20 + -10.0f;

			XMFLOAT3 spawn;
			spawn.x = spawnX;
			spawn.y = 0;
			spawn.z = spawnZ;

			Queue.push_back(new Enemy(spawn));
		}
		if (spawnPointRandom = 4)
		{
			int spawnX = rand() % -40 + -5;
			int spawnZ = rand() % -40 + -5;

			XMFLOAT3 spawn;
			spawn.x = spawnX;
			spawn.y = 0;
			spawn.z = spawnZ;

			Queue.push_back(new Enemy(spawn));
		}
	}
}

void EnemySpawn::Render()
{
	for (unsigned int i = 0; i < Alive.size(); i++)
	{
		Alive.at(i)->Render();
	}
}
