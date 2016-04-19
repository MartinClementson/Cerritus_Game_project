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
	
}

void EnemySpawn::Release()
{

}

void EnemySpawn::Update(double deltaTime)
{
	if (Queue.size() <= 20)
	{
		SpawnEnemy();

		if (Alive.size() <= 10)
		{
			Alive.push_back(Queue.at(0));
			Queue.erase(Queue.begin());
		}
	}
	else
	{
		return;
	}
}

void EnemySpawn::SpawnEnemy()
{
	for (int i = 0; i < 19; i++)
	{
		int spawnPointRandom = rand() % 3 + 1;

		if (spawnPointRandom = 1)
		{
			float spawnX = rand() % 50 + 1;
			float spawnZ = rand() % 50 + 1;

			XMFLOAT3 spawn;
			spawn.x = spawnX;
			spawn.z = spawnZ;

			Queue.push_back( new Enemy(spawn) );
		}
		if (spawnPointRandom = 2)
		{
			float spawnX = rand() % 100 + 50;
			float spawnZ = rand() % 100 + 50;

			XMFLOAT3 spawn;
			spawn.x = spawnX;
			spawn.z = spawnZ;

			Queue.push_back(new Enemy(spawn));
		}
		if (spawnPointRandom = 3)
		{
			float spawnX = rand() % 150 + 100;
			float spawnZ = rand() % 150 + 100;

			XMFLOAT3 spawn;
			spawn.x = spawnX;
			spawn.z = spawnZ;

			Queue.push_back(new Enemy(spawn));
		}
	}
}
