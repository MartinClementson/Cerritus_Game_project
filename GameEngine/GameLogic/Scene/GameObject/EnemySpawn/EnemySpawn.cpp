#include "EnemySpawn.h"



EnemySpawn::EnemySpawn()
{
	this->collision = Collision::GetInstance();
	this->firstSpawn = false;
	nrOfAliveEnemies = 0;
	this->playWave = true;
}

EnemySpawn::~EnemySpawn()
{
	for (size_t i = 0; i < 100; i++)
	{
		delete Alive[i];
	}
}

void EnemySpawn::Initialize(AudioManager* audioManager)
{
	this->audioManager = audioManager;
	graphics = Graphics::GetInstance();
	currentWave = 1;
	waves.SetWaveGroup(currentWave);
	waves.WaveInformation();
	nrOfAliveEnemies = waves.GetWaveInformation();

	WaveComplete.UIobject = UITextures::WAVECOMPLETE;
	WaveCounter.UIobject = UITextures::WAVECOUNTER;
	Leftnr.UIobject = UITextures::LEFTENEMYNR;
	Rightnr.UIobject = UITextures::RIGHTENEMYNR;
	//huden.UIobject = UITextures::HUD;
	//Leftnr.UInumber = UiNumbers::ZERO;
	//Rightnr.UInumber = UiNumbers::ZERO;

	InitEnemy();
}

void EnemySpawn::Release()
{

}

void EnemySpawn::Update(double deltaTime)
{

		for (int i = 0; i < nrOfAliveEnemies; i++)
		{
			Alive[i]->Update(deltaTime);

			if (Alive[i]->GetHealth() <= 0)
			{
				Alive[i]->GetStateMachine()->
				SetActiveState(EnemyState::ENEMY_DEATH_STATE);
				Player* player;
				player = collision->GetPlayer();

				if (Alive[i]->deathAnim == false)
				{
					Alive[i]->deathAnim = true;
					audioManager->playEDeathSound();
				}

				if (Alive[i]->timeToDie == true)
				{
					player->SetPoints(player->GetPoints() + (1.0f*player->GetMulti()));
					player->SetMulti(player->GetMulti() + 0.1f);
					killEnemy(i);
				}
				
				if (nrOfAliveEnemies == 39)
				{
					Leftnr.UInumber = UiNumbers::THREE;
					Rightnr.UInumber = UiNumbers::NINE;


				}
				else if (nrOfAliveEnemies == 38)
				{
					Leftnr.UInumber = UiNumbers::THREE;
					Rightnr.UInumber = UiNumbers::EIGHT;

					//grapichs->QueueRender(&Leftnr);
				}
				else if (nrOfAliveEnemies == 37)
				{
					Leftnr.UInumber = UiNumbers::THREE;
					Rightnr.UInumber = UiNumbers::SEVEN;

					//grapichs->QueueRender(&Leftnr);
				}
				else if (nrOfAliveEnemies == 36)
				{
					Leftnr.UInumber = UiNumbers::THREE;
					Rightnr.UInumber = UiNumbers::SIX;
					Leftnr.UIobject = UITextures::LEFTENEMYNR;
					Rightnr.UIobject = UITextures::RIGHTENEMYNR;

				}
				else if (nrOfAliveEnemies == 35)
				{
					Leftnr.UInumber = UiNumbers::THREE;
					Rightnr.UInumber = UiNumbers::FIVE;
					Leftnr.UIobject = UITextures::LEFTENEMYNR;
					Rightnr.UIobject = UITextures::RIGHTENEMYNR;

				}
				else if (nrOfAliveEnemies == 34)
				{
					Leftnr.UInumber = UiNumbers::THREE;
					Rightnr.UInumber = UiNumbers::FOUR;
					Leftnr.UIobject = UITextures::LEFTENEMYNR;
					Rightnr.UIobject = UITextures::RIGHTENEMYNR;

				}
				else if (nrOfAliveEnemies == 33)
				{
					Leftnr.UInumber = UiNumbers::THREE;
					Rightnr.UInumber = UiNumbers::THREE;
					Leftnr.UIobject = UITextures::LEFTENEMYNR;
					Rightnr.UIobject = UITextures::RIGHTENEMYNR;

				}
				else if (nrOfAliveEnemies == 32)
				{
					Leftnr.UInumber = UiNumbers::THREE;
					Rightnr.UInumber = UiNumbers::TWO;
					Leftnr.UIobject = UITextures::LEFTENEMYNR;
					Rightnr.UIobject = UITextures::RIGHTENEMYNR;

				}
				else if (nrOfAliveEnemies == 31)
				{
					Leftnr.UInumber = UiNumbers::THREE;
					Rightnr.UInumber = UiNumbers::ONE;
					Leftnr.UIobject = UITextures::LEFTENEMYNR;
					Rightnr.UIobject = UITextures::RIGHTENEMYNR;

				}
				
				else if (nrOfAliveEnemies == 29)
				{
					Leftnr.UInumber = UiNumbers::TWO;
					Rightnr.UInumber = UiNumbers::NINE;
					Leftnr.UIobject = UITextures::LEFTENEMYNR;
					Rightnr.UIobject = UITextures::RIGHTENEMYNR;

				}
				else if (nrOfAliveEnemies == 28)
				{
					Leftnr.UInumber = UiNumbers::TWO;
					Rightnr.UInumber = UiNumbers::EIGHT;
					Leftnr.UIobject = UITextures::LEFTENEMYNR;
					Rightnr.UIobject = UITextures::RIGHTENEMYNR;

				}
				else if (nrOfAliveEnemies == 27)
				{
					Leftnr.UInumber = UiNumbers::TWO;
					Rightnr.UInumber = UiNumbers::SEVEN;
					Leftnr.UIobject = UITextures::LEFTENEMYNR;
					Rightnr.UIobject = UITextures::RIGHTENEMYNR;

				}
				else if (nrOfAliveEnemies == 26)
				{
					Leftnr.UInumber = UiNumbers::TWO;
					Rightnr.UInumber = UiNumbers::SIX;
					Leftnr.UIobject = UITextures::LEFTENEMYNR;
					Rightnr.UIobject = UITextures::RIGHTENEMYNR;

				}
				else if (nrOfAliveEnemies == 25)
				{
					Leftnr.UInumber = UiNumbers::TWO;
					Rightnr.UInumber = UiNumbers::FIVE;
					Leftnr.UIobject = UITextures::LEFTENEMYNR;
					Rightnr.UIobject = UITextures::RIGHTENEMYNR;

				}
				else if (nrOfAliveEnemies == 24)
				{
					Leftnr.UInumber = UiNumbers::TWO;
					Rightnr.UInumber = UiNumbers::FOUR;
					Leftnr.UIobject = UITextures::LEFTENEMYNR;
					Rightnr.UIobject = UITextures::RIGHTENEMYNR;

				}
				else if (nrOfAliveEnemies == 23)
				{
					Leftnr.UInumber = UiNumbers::TWO;
					Rightnr.UInumber = UiNumbers::THREE;
					Leftnr.UIobject = UITextures::LEFTENEMYNR;
					Rightnr.UIobject = UITextures::RIGHTENEMYNR;

				}
				else if (nrOfAliveEnemies == 22)
				{
					Leftnr.UInumber = UiNumbers::TWO;
					Rightnr.UInumber = UiNumbers::TWO;
					Leftnr.UIobject = UITextures::LEFTENEMYNR;
					Rightnr.UIobject = UITextures::RIGHTENEMYNR;

				}
				else if (nrOfAliveEnemies == 21)
				{
					Leftnr.UInumber = UiNumbers::TWO;
					Rightnr.UInumber = UiNumbers::ONE;
					Leftnr.UIobject = UITextures::LEFTENEMYNR;
					Rightnr.UIobject = UITextures::RIGHTENEMYNR;

				}
				
				else if (nrOfAliveEnemies == 19)
				{
					Leftnr.UInumber = UiNumbers::ONE;
					Rightnr.UInumber = UiNumbers::NINE;
					Leftnr.UIobject = UITextures::LEFTENEMYNR;
					Rightnr.UIobject = UITextures::RIGHTENEMYNR;

				}
				else if (nrOfAliveEnemies == 18)
				{
					Leftnr.UInumber = UiNumbers::ONE;
					Rightnr.UInumber = UiNumbers::EIGHT;
					Leftnr.UIobject = UITextures::LEFTENEMYNR;
					Rightnr.UIobject = UITextures::RIGHTENEMYNR;

				}
				else if (nrOfAliveEnemies == 17)
				{
					Leftnr.UInumber = UiNumbers::ONE;
					Rightnr.UInumber = UiNumbers::SEVEN;
					Leftnr.UIobject = UITextures::LEFTENEMYNR;
					Rightnr.UIobject = UITextures::RIGHTENEMYNR;

				}
				else if (nrOfAliveEnemies == 16)
				{
					Leftnr.UInumber = UiNumbers::ONE;
					Rightnr.UInumber = UiNumbers::SIX;
					Leftnr.UIobject = UITextures::LEFTENEMYNR;
					Rightnr.UIobject = UITextures::RIGHTENEMYNR;

				}
				else if (nrOfAliveEnemies == 15)
				{
					Leftnr.UInumber = UiNumbers::ONE;
					Rightnr.UInumber = UiNumbers::FIVE;
					Leftnr.UIobject = UITextures::LEFTENEMYNR;
					Rightnr.UIobject = UITextures::RIGHTENEMYNR;

				}
				else if (nrOfAliveEnemies == 14)
				{
					Leftnr.UInumber = UiNumbers::ONE;
					Rightnr.UInumber = UiNumbers::FOUR;
					Leftnr.UIobject = UITextures::LEFTENEMYNR;
					Rightnr.UIobject = UITextures::RIGHTENEMYNR;

				}
				else if (nrOfAliveEnemies == 13)
				{
					Leftnr.UInumber = UiNumbers::ONE;
					Rightnr.UInumber = UiNumbers::THREE;
					Leftnr.UIobject = UITextures::LEFTENEMYNR;
					Rightnr.UIobject = UITextures::RIGHTENEMYNR;

				}
				else if (nrOfAliveEnemies == 12)
				{
					Leftnr.UInumber = UiNumbers::ONE;
					Rightnr.UInumber = UiNumbers::TWO;
					Leftnr.UIobject = UITextures::LEFTENEMYNR;
					Rightnr.UIobject = UITextures::RIGHTENEMYNR;

				}
				else if (nrOfAliveEnemies == 11)
				{
					Leftnr.UInumber = UiNumbers::ONE;
					Rightnr.UInumber = UiNumbers::ONE;
					Leftnr.UIobject = UITextures::LEFTENEMYNR;
					Rightnr.UIobject = UITextures::RIGHTENEMYNR;

				}

				else if (nrOfAliveEnemies == 9)
				{
					Leftnr.UInumber = UiNumbers::ZERO;
					Leftnr.UIobject = UITextures::LEFTENEMYNR;
					Rightnr.UInumber = UiNumbers::NINE;
					Rightnr.UIobject = UITextures::RIGHTENEMYNR;
				}
				else if (nrOfAliveEnemies == 8)
				{
					Leftnr.UInumber = UiNumbers::ZERO;
					Leftnr.UIobject = UITextures::LEFTENEMYNR;
					Rightnr.UInumber = UiNumbers::EIGHT;
					Rightnr.UIobject = UITextures::RIGHTENEMYNR;
				}
				else if (nrOfAliveEnemies == 7)
				{
					Leftnr.UInumber = UiNumbers::ZERO;
					Leftnr.UIobject = UITextures::LEFTENEMYNR;
					Rightnr.UInumber = UiNumbers::SEVEN;
					Rightnr.UIobject = UITextures::RIGHTENEMYNR;
				}
				else if (nrOfAliveEnemies == 6)
				{
					Leftnr.UInumber = UiNumbers::ZERO;
					Leftnr.UIobject = UITextures::LEFTENEMYNR;
					Rightnr.UInumber = UiNumbers::SIX;
					Rightnr.UIobject = UITextures::RIGHTENEMYNR;
				}
				else if (nrOfAliveEnemies == 5)
				{
					Leftnr.UInumber = UiNumbers::ZERO;
					Leftnr.UIobject = UITextures::LEFTENEMYNR;
					Rightnr.UInumber = UiNumbers::FIVE;
					Rightnr.UIobject = UITextures::RIGHTENEMYNR;
				}
				else if (nrOfAliveEnemies == 4)
				{
					Leftnr.UInumber = UiNumbers::ZERO;
					Leftnr.UIobject = UITextures::LEFTENEMYNR;
					Rightnr.UInumber = UiNumbers::FOUR;
					Rightnr.UIobject = UITextures::RIGHTENEMYNR;
				}
				else if (nrOfAliveEnemies == 3)
				{
					Leftnr.UInumber = UiNumbers::ZERO;
					Leftnr.UIobject = UITextures::LEFTENEMYNR;
					Rightnr.UInumber = UiNumbers::THREE;
					Rightnr.UIobject = UITextures::RIGHTENEMYNR;

				}
				else if (nrOfAliveEnemies == 2)
				{
					Leftnr.UInumber = UiNumbers::ZERO;
					Leftnr.UIobject = UITextures::LEFTENEMYNR;
					Rightnr.UInumber = UiNumbers::TWO;
					Rightnr.UIobject = UITextures::RIGHTENEMYNR;

				}
				else if (nrOfAliveEnemies == 1)
				{
					Leftnr.UInumber = UiNumbers::ZERO;
					Leftnr.UIobject = UITextures::LEFTENEMYNR;
					Rightnr.UInumber = UiNumbers::ONE;
					Rightnr.UIobject = UITextures::RIGHTENEMYNR;

				}
				else if (nrOfAliveEnemies == 10)
				{

					Leftnr.UInumber = UiNumbers::ONE;
					Rightnr.UInumber = UiNumbers::ZERO;
					Leftnr.UIobject = UITextures::LEFTENEMYNR;
					Rightnr.UIobject = UITextures::RIGHTENEMYNR;

				}
				else if (nrOfAliveEnemies == 40)
				{
					Leftnr.UInumber = UiNumbers::FOUR;
					Rightnr.UInumber = UiNumbers::ZERO;

				}
				else if (nrOfAliveEnemies == 20)
				{
					Leftnr.UInumber = UiNumbers::TWO;
					Rightnr.UInumber = UiNumbers::ZERO;
					Leftnr.UIobject = UITextures::LEFTENEMYNR;
					Rightnr.UIobject = UITextures::RIGHTENEMYNR;

				}
				else if (nrOfAliveEnemies == 30)
				{
					Leftnr.UInumber = UiNumbers::THREE;
					Rightnr.UInumber = UiNumbers::ZERO;
					Leftnr.UIobject = UITextures::LEFTENEMYNR;
					Rightnr.UIobject = UITextures::RIGHTENEMYNR;

				}
				else if (nrOfAliveEnemies == 0)
				{
					Rightnr.UInumber = UiNumbers::ZERO;			
					Rightnr.UIobject = UITextures::LEFTENEMYNR;			
				}

				//Alive.at(i)->Update(deltaTime);

			}

		}

		if (!firstSpawn)
		{
			if (waves.GetWaveTimer() <= 0)
			{
				SpawnEnemy(nrOfAliveEnemies);
				
				if (nrOfAliveEnemies == 10)
				{
					WaveCounter.UIobject = UITextures::WAVECOUNTER;
					WaveCounter.UInumber = UiNumbers::ONE;
					Leftnr.UInumber = UiNumbers::ONE;
					Rightnr.UInumber = UiNumbers::ZERO;
					Leftnr.UIobject = UITextures::LEFTENEMYNR;
					Rightnr.UIobject = UITextures::RIGHTENEMYNR;
				
				}
				if (nrOfAliveEnemies == 40)
				{
					WaveCounter.UIobject = UITextures::WAVECOUNTER;
					WaveCounter.UInumber = UiNumbers::FOUR;
					Leftnr.UInumber = UiNumbers::FOUR;
					Rightnr.UInumber = UiNumbers::ZERO;
					Leftnr.UIobject = UITextures::LEFTENEMYNR;
					Rightnr.UIobject = UITextures::RIGHTENEMYNR;
					
				}
				if (nrOfAliveEnemies == 20)
				{
					WaveCounter.UIobject = UITextures::WAVECOUNTER;
					WaveCounter.UInumber = UiNumbers::TWO;
					Leftnr.UInumber = UiNumbers::TWO;
					Rightnr.UInumber = UiNumbers::ZERO;
					Leftnr.UIobject = UITextures::LEFTENEMYNR;
					Rightnr.UIobject = UITextures::RIGHTENEMYNR;

				}
				if (nrOfAliveEnemies == 30)
				{
					WaveCounter.UIobject = UITextures::WAVECOUNTER;
					WaveCounter.UInumber = UiNumbers::THREE;
					Leftnr.UInumber = UiNumbers::THREE;
					Rightnr.UInumber = UiNumbers::ZERO;
					Leftnr.UIobject = UITextures::LEFTENEMYNR;
					Rightnr.UIobject = UITextures::RIGHTENEMYNR;

				}
				
				//waveCounter changes. 
			}
			else
			{
				graphics->QueueRender(&WaveComplete);
				if (waves.GetWaveTimer() <= 6 && playWave)
				{
					audioManager->playNewWave();
					playWave = false;
				}
			}
		}

		for (int i = 0; i < nrOfAliveEnemies; i++)
		{
			if (Alive[i]->isAlive == true)
			{
				collision->PlayerCollision(Alive[i]);
				if (!collision->SceneColIn(deltaTime, Alive[i])) //change this
				{
					Alive[i]->position.x = Alive[i]->position.x;
					Alive[i]->position.z = Alive[i]->position.z;
				}
				if (collision->SceneColIn(deltaTime, Alive[i]))
				{
					Alive[i]->position.x = Alive[i]->position.x;
					Alive[i]->position.z = Alive[i]->position.z;
				}
			}
		}
	if (nrOfAliveEnemies == 0)
	{
			waves.SetWaveGroup(currentWave += 1);
			waves.WaveInformation();
			nrOfAliveEnemies = waves.GetWaveInformation();

			pickupRespawn = true;
			playWave = true;
			if (nrOfAliveEnemies == 0)
			{
				win = true;
			}
			
		
			else
				firstSpawn = false;
	}
	waves.Update(deltaTime);
}	

void EnemySpawn::SpawnEnemy(int waveAmount)
{
	float x = 0;

	firstSpawn = true;

	for (int i = 0; i < waveAmount; i++)
	{
		intSpawn = rand() % 4 + 1;

			if (intSpawn == 1)
			{
				waves.SetSpawnPosAdd(x);
				waves.SpawnPositions(1);
				spawn = waves.GetSpawnPositions();
			}
			else if (intSpawn == 2)
			{
				waves.SetSpawnPosAdd(x);
				waves.SpawnPositions(2);
				spawn = waves.GetSpawnPositions();

			}
			else if (intSpawn == 3)
			{
				waves.SetSpawnPosAdd(x);
				waves.SpawnPositions(3);
				spawn = waves.GetSpawnPositions();
			}
			else if (intSpawn == 4)
			{
				waves.SetSpawnPosAdd(x);
				waves.SpawnPositions(4);
				spawn = waves.GetSpawnPositions();
			}

			x += 1;

			Alive[i]->Spawn(spawn);

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
	else if (intSpawn == 2)
	{
		waves.SetSpawnPosAdd(x);
		waves.SpawnPositions(2);
		spawn = waves.GetSpawnPositions();

	}
	else if (intSpawn == 3)
	{
		waves.SetSpawnPosAdd(x);
		waves.SpawnPositions(3);
		spawn = waves.GetSpawnPositions();
	}
	else if (intSpawn == 4)
	{
		waves.SetSpawnPosAdd(x);
		waves.SpawnPositions(4);
		spawn = waves.GetSpawnPositions();
	}
	x += 1;

	Alive[i]->Respawn(spawn);
}

void EnemySpawn::InitEnemy()
{
	unsigned int amount = 80;
	float b = 0;

	for (size_t i = 0; i < 100; i++)
	{
		//nrOfAliveEnemies++;
		int spawnPointRandom = rand() % 5 + 1;

		/*if (spawnPointRandom == 1)
		{
			waves.SetSpawnPosAdd(b);
			waves.SpawnPositions(1);
			spawn = waves.GetSpawnPositions();
			
			fast = false;
			Alive[i] = (new Enemy(spawn, fast));
		}*/
		if (i % 10 || i == 0)
		{
			int spawnPointRandom = rand() % 4 + 1;

			if (spawnPointRandom == 1)
			{
				waves.SetSpawnPosAdd(b);
				waves.SpawnPositions(1);
				spawn = waves.GetSpawnPositions();
				fast = false;
			}
			else if (spawnPointRandom == 2)
			{

				waves.SetSpawnPosAdd(b);
				waves.SpawnPositions(2);
				spawn = waves.GetSpawnPositions();

				fast = true;

			}
			else if (spawnPointRandom == 3)
			{
				waves.SetSpawnPosAdd(b);
				waves.SpawnPositions(3);
				spawn = waves.GetSpawnPositions();

				fast = false;

			}
			else if (spawnPointRandom == 4)
			{
				waves.SetSpawnPosAdd(b);
				waves.SpawnPositions(4);
				spawn = waves.GetSpawnPositions();

				fast = true;

			}

			b += 5;

			Alive[i] = (new Enemy(spawn, fast));
		}
		else
		{
			waves.SetSpawnPosAdd(b);
			waves.SpawnPositions(1);
			spawn = waves.GetSpawnPositions();

			Alive[i] = (new Healer(spawn));
		}

		b += 1;

		Alive[i]->Initialize();

		/*for (int i = 0; i < nrOfAliveEnemies; i++)
		{
			if (Alive[i]->isAlive == true)
			{
				collision->AddEnemy(Alive[i]);
			}
		}*/
	}
}

void EnemySpawn::Render()
{
	for (size_t i = 0; i < nrOfAliveEnemies; i++)
	{
		if (Alive[i]->isAlive == true)
		{
			Alive[i]->Render();
		}
	}
	graphics->QueueRender(&Rightnr);
	graphics->QueueRender(&Leftnr);
	graphics->QueueRender(&WaveCounter);
	//graphics->QueueRender(&huden);
}

void EnemySpawn::killEnemy(int index)
{
	Alive[index]->isAlive = false;
	Alive[index]->SetHealth(100.0f);
	nrOfAliveEnemies--;

	//swapping
	EnemyBase* temp;
	temp = Alive[index];
	Alive[index] = Alive[nrOfAliveEnemies];
	Alive[nrOfAliveEnemies] = temp;
}