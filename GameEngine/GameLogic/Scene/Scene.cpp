#include "Scene.h"



Scene::Scene()
{
	/*this->bearTraps = new std::vector<BearTrap>;
	this->fireTraps = new std::vector<FireTrap>;*/
	this->enemySpawn = new EnemySpawn;
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

}

void Scene::Initialize()
{
	fireTraps.push_back(new FireTrap());

	bearTraps.push_back(new BearTrap());

	enemySpawn->Initialize();
	for (int i = 0; i < fireTraps.size(); i++)
	{
		fireTraps.at(i)->Initialize();
	}
	for (int i = 0; i < bearTraps.size(); i++)
	{
		bearTraps.at(i)->Initialize();
	}

}		



void Scene::Release()
{
	enemySpawn->Release();
}

void Scene::Update(double deltaTime)
{

	for (int i = 0; i < fireTraps.size(); i++)
	{
//		fireTraps.at(i)->GetPosition();
		fireTraps.at(i)->Update(deltaTime);

		if (fireTraps.at(i)->GetDot())
		{
			fireTraps.at(i)->GetDamage();

		}
		/*else if (fireTraps.at(i)->GetDot())
		{
		}	*/
	}
	for (int i = 0; i < bearTraps.size(); i++)
	{
//		bearTraps.at(i)->GetPosition();
		bearTraps.at(i)->Update(deltaTime);
		if (bearTraps.at(i)->GetSlow())
		{
			bearTraps.at(i)->GetDamage();
		}
		/*else if (bearTraps.at(i)->GetSlow())
		{
			
			
		}*/
	}
	enemySpawn->Update(deltaTime);

}

void Scene::Render()
{

//	fireTraps.at(0)->Render();
	for (int i = 0; i < fireTraps.size(); i++)
	{
		if (fireTraps.at(i)->GetDot())
		{
			fireTraps.at(i)->Render();
		}
		
	}
	for (int i = 0; i < bearTraps.size(); i++)
	{
		if (bearTraps.at(i)->GetSlow())
		{
			bearTraps.at(i)->Render();
		}
		
	}
	enemySpawn->Render();

}

void Scene::load()
{

}
