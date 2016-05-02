#include "EnemySpawn.h"

EnemySpawn::EnemySpawn()
{
	this->collision = Collision::GetInstance();
	this->firstSpawn = false;
}

EnemySpawn::~EnemySpawn()
{
	for (size_t i = 0; i < StandardQueue.size(); i++)
	{
			delete StandardQueue.at(i);
	}

	for (size_t i = 0; i < StandardAlive.size(); i++)
	{
		delete StandardAlive.at(i);
	}
}

void EnemySpawn::Initialize(XMFLOAT3 spawnPosition)
{
	waveAmount = 40;
	this->spawnPosition = spawnPosition;
	InitEnemy();
}

void EnemySpawn::Release()
{

}

void EnemySpawn::Update(double deltaTime)
{
	for (size_t i = 0; i < StandardAlive.size(); i++)
	{
		if(collision->PlayerProxyEnemy(StandardAlive.at(i)))
		{
			for (size_t j = 0; j < StandardAlive.size(); j++)
			{
				StandardAlive.at(j)->GetStateMachine()->
					SetActiveState(EnemyState::ENEMY_ATTACK_STATE);
			}
		}
	}


	for (size_t i = 0; i < StandardAlive.size(); i++)
	{
		StandardAlive.at(i)->Update(deltaTime);
		if (StandardAlive.at(i)->GetHealth() <= 0 &&
			StandardAlive.at(i)->GetStateMachine()->
			GetActiveState() == EnemyState::ENEMY_ATTACK_STATE)
		{
			Player* player;
			player = collision->GetPlayer();
			player->SetPoints(player->GetPoints() + (10.0f*player->GetMulti()));
			player->SetMulti(player->GetMulti() + 0.1f);

			StandardAlive.at(i)->isAlive = false;
			StandardAlive.at(i)->SetHealth(100.0f);
			StandardAlive.at(i)->GetStateMachine()->
				SetActiveState(EnemyState::ENEMY_DEATH_STATE);

			StandardQueue.push_back(StandardAlive.at(i));

			StandardAlive.erase(StandardAlive.begin() + i);
		}
		else if (StandardAlive.at(i)->GetHealth() <= 0 &&
			StandardAlive.at(i)->GetStateMachine()->
			GetActiveState() == EnemyState::ENEMY_IDLE_STATE)
		{
			Player* player;
			player = collision->GetPlayer();
			player->SetPoints(player->GetPoints() - 10.0f);
			player->SetMulti(1);

			StandardAlive.at(i)->isAlive = false;
			StandardAlive.at(i)->SetHealth(100.0f);
			StandardAlive.at(i)->GetStateMachine()->
				SetActiveState(EnemyState::ENEMY_DEATH_STATE);

			StandardQueue.push_back(StandardAlive.at(i));

			StandardAlive.erase(StandardAlive.begin() + i);
		}
	}

	if (StandardAlive.size() == 0)
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
		}
	}

	for (int i = 0; i < (int)StandardAlive.size(); i++)
	{
		if (StandardAlive.at(i)->isAlive == true)
		{

			if (collision->PlayerCollision(StandardAlive.at(i)))
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
	
	for(size_t i = 0; i< StandardQueue.size(); i++)
	{
		if (!StandardQueue.at(i)->isAlive)
		{

			float spawnX = spawnPosition.x + float(rand() % 15 + 5.0f);
			float spawnZ = spawnPosition.z + float(rand() % 50 + 5.0f);


			XMFLOAT3 spawn;
			spawn.x = spawnX;
			spawn.y = 0;
			spawn.z = spawnZ;
			
			StandardQueue.at(i)->Spawn(spawn); //sets position and isAlive to TRUE
			StandardAlive.push_back(StandardQueue.at(i));
			StandardQueue.erase(StandardQueue.begin() + i);
			

			//done = true;
		}
		//i++;
	}
}

void EnemySpawn::RespawnEnemy()
{
	

	for (size_t i = 0; i< StandardQueue.size(); i++)
	{
		if (!StandardQueue.at(i)->isAlive)
		{

			float spawnX = spawnPosition.x + float(rand() % 15 + 5.0f);
			float spawnZ = spawnPosition.z + float(rand() % 50 + 5.0f);


			XMFLOAT3 spawn;
			spawn.x = spawnX;
			spawn.y = 0;
			spawn.z = spawnZ;

			StandardQueue.at(i)->Respawn(spawn); //sets position and isAlive to TRUE
			StandardAlive.push_back(StandardQueue.at(i));
			StandardQueue.erase(StandardQueue.begin() + i);


			//done = true;
		}
		//i++;
	}
}

std::vector<Enemy*> EnemySpawn::GetStandardQueue()
{
	return StandardQueue;
}

std::vector<Enemy*> EnemySpawn::GetStandardAlive()
{
	return StandardAlive;
}

std::vector<Enemy*> EnemySpawn::GetFastQueue()
{
	return FastQueue;
}

std::vector<Enemy*> EnemySpawn::GetFastAlive()
{
	return FastAlive;
}

void EnemySpawn::InitEnemy()
{
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

			StandardQueue.push_back( new Enemy(spawn,false) );
		}
		if (spawnPointRandom == 2)
		{
			float spawnX = float(rand() % 15 + 5.0f);
			float spawnZ = float(rand() % 50 + 5.0f);

			XMFLOAT3 spawn;
			spawn.x = spawnX;
			spawn.y = 0;
			spawn.z = spawnZ;

			StandardQueue.push_back( new Enemy(spawn,true) );
		}
		if (spawnPointRandom == 3)
		{
			float spawnX = float(rand() % 15 + 5.0f);
			float spawnZ = float(rand() % 50 + 5.0f);

			XMFLOAT3 spawn;
			spawn.x = spawnX;
			spawn.y = 0;
			spawn.z = spawnZ;

			StandardQueue.push_back(new Enemy(spawn,false));
		}
		if (spawnPointRandom == 4)
		{
			float spawnX = float(rand() % 15 + 5.0f);
			float spawnZ = float(rand() % 50 + 5.0f);

			XMFLOAT3 spawn;
			spawn.x = spawnX;
			spawn.y = 0;
			spawn.z = spawnZ;

			StandardQueue.push_back(new Enemy(spawn, true));
		}
	}
	for(int i = 0; i < (int)StandardQueue.size(); i++)
	{ 
		collision->AddEnemy(StandardQueue.at(i));
	}
}

void EnemySpawn::Render()
{
	for (unsigned int i = 0; i < (int)StandardAlive.size(); i++)
	{
		
		StandardAlive.at(i)->Render();
		
	}
}
