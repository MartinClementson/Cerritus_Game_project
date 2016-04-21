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

void EnemySpawn::Initialize()
{
	InitEnemy();
}

void EnemySpawn::Release()
{

}
void EnemySpawn::Update(double deltaTime)
{
	if (Alive.size() <= 10)
	{
		SpawnEnemy();
	}
	for (int i = 0; i < Alive.size(); i++)
	{
		if (collision->PlayerCollision(Alive.at(i))&& Alive.at(i)->isAlive == true)
		{
			////not alive anymore
			//MessageBox(0, L"You have Collided",
			//	L"LOL", MB_OK);
		
			Alive.at(i)->isAlive = false;
			Queue.push_back(Alive.at(i));	
			Alive.erase(Alive.begin() + i);
		}
	}

}

void EnemySpawn::SpawnEnemy()
{
	bool done = false;
	int i = 0;
	while (done == false || i > Queue.size())
	{
		if (!Queue.at(i)->isAlive)
		{
			Queue.at(i)->isAlive = true;
			Alive.push_back(Queue.at(i));
			Queue.erase(Queue.begin() + i);
			

			done = true;
		}
		i++;
	}
}

void EnemySpawn::InitEnemy()
{
	unsigned int waveAmount = 20;

	XMFLOAT3 spawnPosition = {150.0f, 0.0f, 50.0f};

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
	for(int i = 0; i < Queue.size(); i++)
	{ 
		collision->AddEnemy(Queue.at(i));
		bool test;
	}
}

void EnemySpawn::Render()
{
	for (unsigned int i = 0; i < Alive.size(); i++)
	{
		if (Alive.at(i)->isAlive)
		{
			Alive.at(i)->Render();
		}
	}
}
