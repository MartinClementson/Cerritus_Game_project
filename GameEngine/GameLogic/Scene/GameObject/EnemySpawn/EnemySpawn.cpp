#include "EnemySpawn.h"



EnemySpawn::EnemySpawn()
{
	//this->enemies = new std::vector<Enemy>;
}


EnemySpawn::~EnemySpawn()
{
	delete this->enemies;
}

void EnemySpawn::Initialize()
{
	for (int i = 0; i < enemies->size(); i++)
	{
		float spawnX = rand() % 200 + 1;
		float spawnZ = rand() % 200 + 1;

		XMVECTOR spawn = { spawnX, 0, spawnZ, 0 };

		Enemy enemy;

		enemy.Initialize(spawn);
	}
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
