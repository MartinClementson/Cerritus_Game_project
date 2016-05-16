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
	fireTrapAmount = 3;
	slowTrapAmount = 5;
	collision->ClearTraps();
	InitBearTrap();
	InitFireTrap();

	

	Pickups.push_back(new Pickup(XMFLOAT3(41.765f, 1.0f, 292.007f), PickupType::WEAPON));
	Pickups.push_back(new Pickup(XMFLOAT3(-74.565f, 1.0f, 146.426f), PickupType::WEAPON));
	Pickups.push_back(new Pickup(XMFLOAT3(87.982f, 1.0f, -103.119f), PickupType::WEAPON));

	Pickups.push_back(new Pickup(XMFLOAT3(79.973f, 1.0f, 98.081f), PickupType::HEAL));
	Pickups.push_back(new Pickup(XMFLOAT3(-68.137f, 1.0f, 280.096f), PickupType::HEAL));

	RespawnTimer = 0;

	enemySpawn->Initialize();

}

void Scene::InitFireTrap()
{
	for (int i = 0; i < fireTrapAmount; i++)
	{
		XMFLOAT3 tmp; // randomizes the location of the firetrap
		tmp.x = -23.438f;
		tmp.y = 0.1f;
		tmp.z = 196.672f;
		fireTraps.push_back(new FireTrap(tmp));
		tmp.x = 5.722f;
		tmp.y = 0.1f;
		tmp.z = -44.001f;
		fireTraps.push_back(new FireTrap(tmp));
		tmp.x = -75.777f;
		tmp.y = 0.1f;
		tmp.z = 77.070f;
		fireTraps.push_back(new FireTrap(tmp));
	}

}

void Scene::InitBearTrap()
{
	for (int i = 0; i < slowTrapAmount; i++)
	{
		XMFLOAT3 tmp; // randomizes the location of the beartrap
		tmp.x = 29.924f;
		tmp.y = 0.1f;
		tmp.z = 246.448f;
		BearTrap* temp = new BearTrap(tmp);
		temp->Initialize(tmp, temp->GetRotation());
		bearTraps.push_back(temp);
		tmp.x = 39.686f;
		tmp.y = 0.1f;
		tmp.z = 172.339f;
		temp = new BearTrap(tmp);
		temp->Initialize(tmp, temp->GetRotation());
		bearTraps.push_back(temp);
		tmp.x = 30.121f;
		tmp.y = 0.1f;
		tmp.z = 34.963f;
		temp = new BearTrap(tmp);
		temp->Initialize(tmp, temp->GetRotation());
		bearTraps.push_back(temp);
		tmp.x = -60.656f;
		tmp.y = 0.1f;
		tmp.z = -26.118f;
		temp = new BearTrap(tmp);
		temp->Initialize(tmp, temp->GetRotation());
		bearTraps.push_back(temp);
		tmp.x = 39.686f;
		tmp.y = 0.1f;
		tmp.z = -70.199f;
		temp = new BearTrap(tmp);
		temp->Initialize(tmp, temp->GetRotation());
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

				bearTraps.at(i)->GetState()->SetTrapState(TrapState::TRAP_INACTIVE_STATE);
				continue;
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

					bearTraps.at(i)->GetState()->SetTrapState(TrapState::TRAP_INACTIVE_STATE);
					continue;
				}
			}	
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