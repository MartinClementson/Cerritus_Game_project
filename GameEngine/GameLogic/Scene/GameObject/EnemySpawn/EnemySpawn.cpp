#include "EnemySpawn.h"

EnemySpawn::EnemySpawn()
{
	this->collision = Collision::GetInstance();
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
	InitEnemy();
}

void EnemySpawn::Release()
{

}

void EnemySpawn::Update(double deltaTime)
{
	for (size_t i = 0; i < Alive.size(); i++)
	{
		Alive.at(i)->Update(deltaTime);

		if (collision->PlayerCollision(Alive.at(i)))
		{
			//Alive.at(i)->SetHealth(0.0f);
		}

		if (Alive.at(i)->GetHealth() <= 0 && Alive.at(i)->isAlive == true)
		{
			Alive.at(i)->isAlive = false;
			Alive.at(i)->SetHealth(100.0f);

			Queue.push_back(Alive.at(i));
			Alive.erase(Alive.begin() + i);
		}		
	}
	if (Alive.size() < 5)
	{
		SpawnEnemy();
	}

}
	

void EnemySpawn::SpawnEnemy()
{
	bool done = false;
	int i = 0;

	while (done == false || i > (int)Queue.size())
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
			

			done = true;
		}
		i++;
	}
}

void EnemySpawn::InitEnemy()
{
	unsigned int waveAmount = 12;


	for (size_t i = 0; i < waveAmount; i++)
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

void EnemySpawn::Render()
{
	for (unsigned int i = 0; i < (int)Alive.size(); i++)
	{
		
			Alive.at(i)->Render();
		
	}
}
