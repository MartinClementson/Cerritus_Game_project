#include "Scene.h"
#include <time.h>

Scene::Scene()
{
	/*this->bearTraps = new std::vector<BearTrap>;
	this->fireTraps = new std::vector<FireTrap>;*/

	//enemySpawn = new EnemySpawn;

	this->enemySpawn = new EnemySpawn;

	//this->trap = new Trap;
	collision = Collision::GetInstance();
}

Scene::~Scene()
{

	delete this->enemySpawn;	

	/*delete this->sceneModels;
	delete this->sceneLights;
	delete this->enemySpawns;*/
	//delete this->bearTraps;
	//delete this->fireTraps;
	for (unsigned int i = 0; i < fireTraps.size(); i++)
	{
		if (fireTraps.at(i))
			delete fireTraps.at(i);
	}
	for (unsigned int i = 0; i < bearTraps.size(); i++)
	{
		if (bearTraps.at(i))
			delete bearTraps.at(i);
	}
	for (size_t i = 0; i < Pickups.size(); i++)
	{
		if (Pickups.at(i))
			delete Pickups.at(i);
		
	}

}

void Scene::Initialize()
{
	trapAmount = 4;
	collision->ClearTraps();
	InitBearTrap();
	InitFireTrap();

	Pickups.push_back(new Pickup(XMFLOAT3(10, 1, -20), PickupType::Weapon));
	Pickups.push_back(new Pickup(XMFLOAT3(20, 1, -10), PickupType::Weapon));
	Pickups.push_back(new Pickup(XMFLOAT3(30, 1, 0), PickupType::Weapon));
	Pickups.push_back(new Pickup(XMFLOAT3(40, 1, 10), PickupType::Weapon));
	Pickups.push_back(new Pickup(XMFLOAT3(50, 1, 20), PickupType::Weapon));

	Pickups.push_back(new Pickup(XMFLOAT3(-10, 1, -20), PickupType::Heal));
	Pickups.push_back(new Pickup(XMFLOAT3(-20, 1, -10), PickupType::Heal));
	Pickups.push_back(new Pickup(XMFLOAT3(-30, 1, 0), PickupType::Heal));
	Pickups.push_back(new Pickup(XMFLOAT3(-40, 1, 10), PickupType::Heal));
	Pickups.push_back(new Pickup(XMFLOAT3(-50, 1, 20), PickupType::Heal));

	RespawnTimer = 0;

	enemySpawn->Initialize();

}

void Scene::InitFireTrap()
{
	srand((unsigned int)time(0));


	for (int i = 0; i < trapAmount; i++)
	{
		XMFLOAT3 tmp; // randomizes the location of the beartrap
		tmp.x = rand() % 150 - 85.0f;
		tmp.y = 0;
		tmp.z = rand() % 150 - 65.0f;
		XMFLOAT3 pos = { tmp.x,tmp.y,tmp.z };
		fireTraps.push_back(new FireTrap(pos));
	}

}

void Scene::InitBearTrap()
{
	srand((unsigned int)time(0));


	for (int i = 0; i < trapAmount; i++)
	{
		XMFLOAT3 tmp; // randomizes the location of the beartrap
		tmp.x = rand() % 150 - 65.0f;
		tmp.y = 0;
		tmp.z = rand() % 150 - 85.0f;
		XMFLOAT3 pos = { tmp.x,tmp.y,tmp.z };
		BearTrap* temp = new BearTrap(pos);
		temp->Initialize(pos, temp->GetRotation());
		bearTraps.push_back(temp);
	}
}

void Scene::Release()
{
	this->enemySpawn->Release();
}

void Scene::Update(double deltaTime)
{
	for (size_t i = 0; i < Pickups.size(); i++)
	{
		Pickups.at(i)->Update(deltaTime);
	}

	enemySpawn->Update(deltaTime);

	if (enemySpawn->win == true)
	{
		toWin = true;
	}

	for (size_t i = 0; i < fireTraps.size(); i++)
	{
		fireTraps.at(i)->Update(deltaTime);

		if (fireTraps.at(i)->GetDot())
		{
			fireTraps.at(i)->GetDamage();
		}
	}

	for (size_t i = 0; i < bearTraps.size(); i++)
	{
		bearTraps.at(i)->Update(deltaTime);
		if (bearTraps.at(i)->GetSlow())
		{
			bearTraps.at(i)->GetDamage();
		}
	}

	for (size_t i = 0; i < bearTraps.size(); i++)
	{
		if (bearTraps.at(i)->GetState()->GetTrapState() != TrapState::TRAP_INACTIVE_STATE)
		{
			if (collision->BearTrapPlayerCollision(bearTraps.at(i)))
			{
				collision->PlayerProxyTrap(bearTraps.at(i));

				for (size_t k = 0; k < enemySpawn->Alive.size(); k++)
				{
					collision->EnemyProxTrap(bearTraps.at(i),
						enemySpawn->Alive.at(k));
				}
				bearTraps.at(i)->GetState()->SetTrapState(TrapState::TRAP_ACTIVE_STATE);
			}
		}

			for (size_t k = 0; k < enemySpawn->Alive.size(); k++)
			{
				if (collision->BearTrapEnemyCollision(bearTraps.at(i),
					enemySpawn->Alive.at(k)))
				{
					collision->PlayerProxyTrap(bearTraps.at(i));

					for (size_t k2 = 0; k2 < enemySpawn->Alive.size(); k2++)
					{
						collision->EnemyProxTrap(bearTraps.at(i),
							enemySpawn->Alive.at(k2));
					}

				}
					bearTraps.at(i)->GetState()->SetTrapState(TrapState::TRAP_ACTIVE_STATE);
			}	
	}

	for (size_t i = 0; i < fireTraps.size(); i++)
	{

		if (fireTraps.at(i)->GetState()->GetTrapState() != TrapState::TRAP_INACTIVE_STATE)
		{
			if (collision->FireTrapPlayerCollision(fireTraps.at(i)))
			{
				fireTraps.at(i)->GetState()->SetTrapState(TrapState::TRAP_ACTIVE_STATE);
			}

			for (size_t k = 0; k < enemySpawn->Alive.size(); k++)
			{
				if (collision->FireTrapEnemyCollision(fireTraps.at(i),
					enemySpawn->Alive.at(k)))
				{
					fireTraps.at(i)->GetState()->SetTrapState(TrapState::TRAP_ACTIVE_STATE);
				}
			}
		}
	}

	if (RespawnTimer >= (double)10)
	{
		for (int i = 0; i < trapAmount - 1; i++)
		{
			fireTraps.at(i)->isActive = true;
			bearTraps.at(i)->isActive = true;
			RespawnTimer = 0;
		}
	}

	else
	{
		RespawnTimer += deltaTime;
	}

}

void Scene::Render()
{
	for (size_t i = 0; i < fireTraps.size(); i++)
	{
		if (fireTraps.at(i)->isActive)
		{
			fireTraps.at(i)->Render();
		}

	}
	for (size_t i = 0; i < bearTraps.size(); i++)
	{
		if (bearTraps.at(i)->isActive)
		{
			bearTraps.at(i)->Render();
		}

	}

	for (size_t i = 0; i < Pickups.size(); i++)
	{
		Pickups.at(i)->Render();
	}

	enemySpawn->Render();
}

void Scene::EvadeTrap(EnemyBase* enemy, BearTrap* bear, double deltaTime)
{
	XMFLOAT3 enemyPos;
	XMFLOAT3 trapPos;
	float trapRadius;
	Vec3 dir;

	trapRadius = bear->GetRadius2();
	enemyPos = enemy->GetPosition();
	trapPos = bear->GetPosition();

	dir.x = trapPos.x - enemyPos.x;
	dir.z = trapPos.z - enemyPos.z;

	dir.Normalize();

	enemy->position.x -= dir.x * (float)deltaTime /* * enemy->movementSpeed*/;
	enemy->position.z -= dir.z * (float)deltaTime /** enemy->movementSpeed*/;

	/*enemy->position.x = dir.x += trapRadius;
	enemy->position.y = dir.y += trapRadius;*/
	/** (float)deltaTime * enemy->movementSpeed*/
	//enemy->position.z = trapRadius /** (float)deltaTime * enemy->movementSpeed*/;
}