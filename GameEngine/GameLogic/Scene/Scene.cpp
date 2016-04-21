#include "Scene.h"



Scene::Scene()
{
	/*this->bearTraps = new std::vector<BearTrap>;
	this->fireTraps = new std::vector<FireTrap>;*/
	
}


Scene::~Scene()
{

	for (size_t i = 0; i < enemySpawns.size(); i++)
	{

	delete this->enemySpawns.at(i);
	}
	
	
	/*delete this->sceneModels;
	delete this->sceneLights;
	delete this->enemySpawns;*/
	//delete this->bearTraps;
	//delete this->fireTraps;
}

void Scene::Initialize()
{
	//fireTraps.push_back(new FireTrap());

	//bearTraps.push_back(new BearTrap());

	
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
		fireTraps.at(i)->GetPosition();
		fireTraps.at(i)->Update(deltaTime);
		if (fireTraps.at(i)->GetDot() == 0)
		{

		}
		else if (fireTraps.at(i)->GetDot() > 0)
		{
			fireTraps.at(i)->GetDamage();
		}	
	}
	for (size_t i = 0; i < bearTraps.size(); i++)
	{
		bearTraps.at(i)->GetPosition();
		bearTraps.at(i)->Update(deltaTime);
		if (bearTraps.at(i)->GetSlow() == 0)
		{

		}
		else if (bearTraps.at(i)->GetSlow() > 0)
		{
			bearTraps.at(i)->GetDamage();
		}
	}
	for (size_t i = 0; i < enemySpawns.size(); i++)
	{

		enemySpawns.at(i)->Update(deltaTime);
	}

}

void Scene::Render()
{
	for (size_t i = 0; i < fireTraps.size(); i++)
	{
		fireTraps.at(i)->Render();
	}
	for (size_t i = 0; i < bearTraps.size(); i++)
	{
		bearTraps.at(i)->Render();
	}

	for (size_t i = 0; i < enemySpawns.size(); i++)
	{

		enemySpawns.at(i)->Render();
	}
	

}

void Scene::load()
{

}
