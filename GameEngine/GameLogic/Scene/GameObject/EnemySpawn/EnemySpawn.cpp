#include "EnemySpawn.h"



EnemySpawn::EnemySpawn()
{
	
}


EnemySpawn::~EnemySpawn()
{
	for (int i = 0; i < enemies.size(); i ++)
	{
		delete enemies.at(i);
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
	
}

void EnemySpawn::Render()
{

}

void EnemySpawn::SpawnEnemy()
{
	for (int i = 0; i < enemies.size(); i++)
	{
		int spawnPointRandom = rand() % 3 + 1;

		if (spawnPointRandom = 1)
		{
			float spawnX = rand() % 50 + 1;
			float spawnZ = rand() % 50 + 1;

			XMFLOAT3 spawn;
			spawn.x = spawnX;
			spawn.z = spawnZ;

			enemies.push_back( new Enemy(spawn) );

		}
		if (spawnPointRandom = 2)
		{
			float spawnX = rand() % 100 + 50;
			float spawnZ = rand() % 100 + 50;

			XMFLOAT3 spawn;
			spawn.x = spawnX;
			spawn.z = spawnZ;

			enemies.push_back(new Enemy(spawn));

		}
		if (spawnPointRandom = 3)
		{
			float spawnX = rand() % 150 + 100;
			float spawnZ = rand() % 150 + 100;

			XMFLOAT3 spawn;
			spawn.x = spawnX;
			spawn.z = spawnZ;

			enemies.push_back(new Enemy(spawn));

		}
	}
}
