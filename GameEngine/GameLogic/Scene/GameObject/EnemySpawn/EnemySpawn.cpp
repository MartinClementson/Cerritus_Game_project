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
	SpawnEnemy();
}
void EnemySpawn::Release()
{

}
void EnemySpawn::Update(double deltaTime)
{
	//for (int i = 0; i < Alive.size(); i++)
	//{
	///*	if (Alive.at(i)->DeadBool == true)
	//	{*/
	//		if (Alive.size() <= 10)
	//		{
	//			Alive.push_back.at(i)(Queue);
	//			Alive.push_back(Queue.at(0));
	//			Queue.erase(Queue.begin());
	//		}
	//	/*}*/
	//}
}

void EnemySpawn::SpawnEnemy()
{
	unsigned int waveAmount = 19;

	for (int i = 0; i < waveAmount; i++)
	{
		int spawnPointRandom = rand() % 4 + 1;

		if (spawnPointRandom = 1)
		{
			float spawnX = rand() % 50 + 1.0f;
			float spawnZ = rand() % 50 + 1.0f;

			XMFLOAT3 spawn;
			spawn.x = spawnX;
			spawn.z = spawnZ;

			Queue.push_back( new Enemy(spawn) );
		}
		if (spawnPointRandom = 2)
		{
			float spawnX = rand() % 100 + 50.0f;
			float spawnZ = rand() % 100 + 50.0f;

			XMFLOAT3 spawn;
			spawn.x = spawnX;
			spawn.z = spawnZ;

			Queue.push_back( new Enemy(spawn) );
		}
		if (spawnPointRandom = 3)
		{
			float spawnX = rand() % 150 + 100.0f;
			float spawnZ = rand() % 150 + 100.0f;

			XMFLOAT3 spawn;
			spawn.x = spawnX;
			spawn.z = spawnZ;

			Queue.push_back(new Enemy(spawn));
		}
		if (spawnPointRandom = 4)
		{
			int spawnX = rand() % 200 + 150;
			int spawnZ = rand() % 200 + 150;

			XMFLOAT3 spawn;
			spawn.x = spawnX;
			spawn.z = spawnZ;

			Queue.push_back(new Enemy(spawn));
		}
	}
}
