#include "EnemySpawn.h"

EnemySpawn::EnemySpawn()
{
	this->collision = Collision::GetInstance();
	this->firstSpawn = false;
}

EnemySpawn::~EnemySpawn()
{
<<<<<<< HEAD
	for (size_t i = 0; i < Alive.size(); i++)
=======
	for (size_t i = 0; i < StandardQueue.size(); i++)
	{
		delete StandardQueue.at(i);
	}

	for (size_t i = 0; i < StandardAlive.size(); i++)
>>>>>>> refs/remotes/origin/master
	{
		delete StandardAlive.at(i);
	}
}

void EnemySpawn::Initialize()
{
<<<<<<< HEAD
	currentWave = 1;
	waves.SetWaveGroup(currentWave);
	waves.WaveInformation();
	waveAmount = waves.GetWaveInformation();
=======
	waveAmount = 5;
	this->spawnPosition = spawnPosition;
>>>>>>> refs/remotes/origin/master
	InitEnemy();
	
}

void EnemySpawn::Release()
{

}

void EnemySpawn::Update(double deltaTime)
{
<<<<<<< HEAD
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

				waveAmount--;

			/*	for (size_t i = 0; i < Alive.size(); i++)
				{
					if (Alive.at(i)->isAlive = true)
					{
						test = false;
					}
					else if(Alive.at(i)->isAlive = false)
					{
						test = true;
					}
				}*/

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
=======


	for (size_t i = 0; i < StandardAlive.size(); i++)
	{
		StandardAlive.at(i)->Update(deltaTime);
		if (StandardAlive.at(i)->GetStateMachine()->
			GetActiveState() == EnemyState::ENEMY_IDLE_STATE)
		{
			if (collision->PlayerProxyEnemy(StandardAlive.at(i)))
			{
				for (size_t j = 0; j < StandardAlive.size(); j++)
				{
					StandardAlive.at(j)->GetStateMachine()->
						SetActiveState(EnemyState::ENEMY_ATTACK_STATE);
				}
			}
		}
		if (StandardAlive.at(i)->GetHealth() <= 0 &&
			StandardAlive.at(i)->GetStateMachine()->
			GetActiveState() == EnemyState::ENEMY_ATTACK_STATE
			)
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
			StandardAlive.shrink_to_fit();
		}
		else if (StandardAlive.at(i)->GetHealth() <= 0 &&
			StandardAlive.at(i)->GetStateMachine()->
			GetActiveState() == EnemyState::ENEMY_HEAL_STATE
			)
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
>>>>>>> refs/remotes/origin/master
	{
		if (StandardAlive.at(i)->isAlive == true)
		{
<<<<<<< HEAD
				
			if (collision->PlayerCollision(Alive.at(i)))

=======

			if (collision->PlayerCollision(StandardAlive.at(i)))
>>>>>>> refs/remotes/origin/master
			{
				Player* player;
				player = collision->GetPlayer();
			}
		}
	}	
}
<<<<<<< HEAD
=======


>>>>>>> refs/remotes/origin/master

void EnemySpawn::SpawnEnemy(int waveAmount)
{
	float x = 0;

	firstSpawn = true;
<<<<<<< HEAD
=======
	
	for(size_t i = 0; i< StandardQueue.size(); i++)
	{
		if (!StandardQueue.at(i)->isAlive)
		{
>>>>>>> refs/remotes/origin/master

	for (int i = 0; i < waveAmount; i++)
	{
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

<<<<<<< HEAD
			Alive.at(i)->Spawn(spawn);
=======
			XMFLOAT3 spawn;
			spawn.x = spawnX;
			spawn.y = 0;
			spawn.z = spawnZ;
			
			StandardQueue.at(i)->Spawn(spawn); //sets position and isAlive to TRUE
			StandardAlive.push_back(StandardQueue.at(i));
			//StandardQueue.erase(StandardQueue.begin() + i);
			
>>>>>>> refs/remotes/origin/master

	}
	StandardQueue.clear();
}

void EnemySpawn::RespawnEnemy(int i)
{
	float x = 0;
	intSpawn = rand() % 4 + 1;

<<<<<<< HEAD
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
=======
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
			//StandardQueue.erase(StandardQueue.begin() + i);

		}
	}

	StandardQueue.clear();
}

std::vector<EnemyBase*> EnemySpawn::GetStandardQueue()
>>>>>>> refs/remotes/origin/master
{
	return StandardQueue;
}

<<<<<<< HEAD
	unsigned int amount = 32;
	float b = 0;

	for (int i = 0; i < amount; i++)
	{
		intSpawn = rand() % 4 + 1;
=======
std::vector<EnemyBase*> EnemySpawn::GetStandardAlive()
{
	return StandardAlive;
}

void EnemySpawn::InitEnemy()
{
	for (size_t i = 0; i < waveAmount; i++)
	{
		int spawnPointRandom = rand() % 5 + 1;
>>>>>>> refs/remotes/origin/master

		if (intSpawn == 1)
		{
<<<<<<< HEAD
			waves.SetSpawnPosAdd(b);
			waves.SpawnPositions(1);
			spawn = waves.GetSpawnPositions();
=======
			float spawnX = float(rand() % 15 + 5.0f);
			float spawnZ = float(rand() % 50 + 5.0f);

			XMFLOAT3 spawn;
			spawn.x = spawnX;
			spawn.y = 0;
			spawn.z = spawnZ;

			StandardQueue.push_back(new Enemy(spawn, false));
>>>>>>> refs/remotes/origin/master
		}
		if (intSpawn == 2)
		{
<<<<<<< HEAD
			waves.SetSpawnPosAdd(b);
			waves.SpawnPositions(2);
			spawn = waves.GetSpawnPositions();
=======
			float spawnX = float(rand() % 15 + 5.0f);
			float spawnZ = float(rand() % 50 + 5.0f);

			XMFLOAT3 spawn;
			spawn.x = spawnX;
			spawn.y = 0;
			spawn.z = spawnZ;

			StandardQueue.push_back(new Enemy(spawn, true));
>>>>>>> refs/remotes/origin/master
		}
		if (intSpawn == 3)
		{
<<<<<<< HEAD
			waves.SetSpawnPosAdd(b);
			waves.SpawnPositions(3);
			spawn = waves.GetSpawnPositions();
=======
			float spawnX = float(rand() % 15 + 5.0f);
			float spawnZ = float(rand() % 50 + 5.0f);

			XMFLOAT3 spawn;
			spawn.x = spawnX;
			spawn.y = 0;
			spawn.z = spawnZ;

			StandardQueue.push_back(new Enemy(spawn, false));
>>>>>>> refs/remotes/origin/master
		}
		if (intSpawn == 4)
		{
			waves.SetSpawnPosAdd(b);
			waves.SpawnPositions(4);
			spawn = waves.GetSpawnPositions();
		}

		b += 5;

		Alive.push_back(new Enemy(spawn));

<<<<<<< HEAD
	}
	for(int i = 0; i < (int)Alive.size(); i++)
	{ 
		if (Alive.at(i)->isAlive == true)
		{
			collision->AddEnemy(Alive.at(i));
		}
=======
			StandardQueue.push_back(new Enemy(spawn, true));
		}
		if (spawnPointRandom == 5)
		{
			float spawnX = float(rand() % 15 + 5.0f);
			float spawnZ = float(rand() % 50 + 5.0f);

			XMFLOAT3 spawn;
			spawn.x = spawnX;
			spawn.y = 0;
			spawn.z = spawnZ;

			StandardQueue.push_back(new Healer(spawn));

			//For test 
			//StandardQueue.push_back(new Enemy(spawn, true));
			
		}
	}
	for(int i = 0; i < (int)StandardQueue.size(); i++)
	{ 
		collision->AddEnemy(StandardQueue.at(i));
>>>>>>> refs/remotes/origin/master
	}
}

void EnemySpawn::Render()
{
<<<<<<< HEAD
	for (size_t i = 0; i < Alive.size(); i++)
	{
		if (Alive.at(i)->isAlive == true)
		{
			Alive.at(i)->Render();
		}
=======
	for (unsigned int i = 0; i < (int)StandardAlive.size(); i++)
	{
		
		StandardAlive.at(i)->Render();
		
>>>>>>> refs/remotes/origin/master
	}
}
