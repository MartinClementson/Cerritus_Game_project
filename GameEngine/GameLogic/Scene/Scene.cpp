#include "Scene.h"
#include <time.h>



Scene::Scene()
{
	/*this->bearTraps = new std::vector<BearTrap>;
	this->fireTraps = new std::vector<FireTrap>;*/
//	this->enemySpawn = new EnemySpawn;
	//this->trap = new Trap;
	collision = Collision::GetInstance();

}


Scene::~Scene()
{

	//delete this->enemySpawn;
//	delete this->trap;


	for (size_t i = 0; i < enemySpawns.size(); i++)
	{

	delete this->enemySpawns.at(i);
	}
	
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

}

void Scene::Initialize()
{
	srand(time(0));
	trapAmount = 5;
	InitBearTrap();
	InitFireTrap();
	RespawnTimer = 0;
}	

void Scene::InitFireTrap()
{
	srand(time(0));


	for (int i = 0; i < trapAmount; i++)
	{
		XMFLOAT3 tmp; // randomizes the location of the beartrap
		tmp.x = rand() % -22 - 3.0f;
		tmp.y = 0;
		tmp.z = rand() % -22 - 3.0f;
		XMFLOAT3 pos = { tmp.x,tmp.y,tmp.z };
		fireTraps.push_back(new FireTrap(pos));
	}
	
}

void Scene::InitBearTrap()
{
	srand(time(0));
	

	for (int i = 0; i < trapAmount; i++)
	{
		XMFLOAT3 tmp; // randomizes the location of the beartrap
		tmp.x = rand() % 22 + 3.0f;
		tmp.y = 0;
		tmp.z = rand() % 22 + 3.0f;
		XMFLOAT3 pos = { tmp.x,tmp.y,tmp.z };
		BearTrap* temp = new BearTrap(pos);
		temp->Initialize(pos,temp->GetRotation());
		bearTraps.push_back(temp);
	}
}

	


void Scene::AddEnemySpawn(XMFLOAT3 spawnPosition)
{
	EnemySpawn* spawnPoint = new EnemySpawn();
	spawnPoint->Initialize(spawnPosition);
	enemySpawns.push_back(spawnPoint);
}




void Scene::Release()
{
	for (size_t i = 0; i < enemySpawns.size(); i++)
	{

		 this->enemySpawns.at(i)->Release();
	}
	
}

void Scene::Update(double deltaTime)
{
	
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
	for (size_t i = 0; i < enemySpawns.size(); i++)
	{
		enemySpawns.at(i)->Update(deltaTime);
	}

	for (size_t i = 0; i < bearTraps.size(); i++)
	{
		if (collision->bearTrapPlayerCollision(bearTraps.at(i)))
		{
			if (bearTraps.at(i)->isActive)
			{
				bearTraps.at(i)->isActive = false;
			}
		}
	}

	for (size_t i = 0; i < fireTraps.size(); i++)
	{
		if (collision->fireTrapPlayerCollision(fireTraps.at(i)) && fireTraps.at(i)->isActive)
		{
			fireTraps.at(i)->isActive = false;
		}
	}
	if (RespawnTimer >= (double)10)
	{ 
		for (int i = 0; i < trapAmount-1; i++)
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
		if (fireTraps.at(i)->GetDot())
		{
			fireTraps.at(i)->Render();
		}
		
	}
	for (size_t i = 0; i < bearTraps.size(); i++)
	{
		if (bearTraps.at(i)->GetSlow())
		{
			bearTraps.at(i)->Render();
		}
		
	}

//	enemySpawn->Render();


	for (size_t i = 0; i < enemySpawns.size(); i++)
	{

		enemySpawns.at(i)->Render();
	}
	
}

void Scene::load()
{

}
