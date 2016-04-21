#include "Scene.h"
#include <time.h>



Scene::Scene()
{
	/*this->bearTraps = new std::vector<BearTrap>;
	this->fireTraps = new std::vector<FireTrap>;*/
	this->enemySpawn = new EnemySpawn;
	//this->trap = new Trap;
}


Scene::~Scene()
{
	delete this->enemySpawn;
//	delete this->trap;
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
	fireTraps.push_back(new FireTrap());

	bearTraps.push_back(new BearTrap());
	
	//trap->Initialize();
	
	enemySpawn->Initialize();
	for (int i = 0; i < fireTraps.size(); i++)
	{
		//trap->Initialize();
	
		XMFLOAT3 tmp;
		tmp.x = rand() % 12;
		tmp.y = 2;
		tmp.z = rand() % 12;

		XMFLOAT3 pos = { tmp.x,tmp.y,tmp.z };

		fireTraps.at(i)->Initialize(pos, fireTraps.at(i)->GetRotation());
	}
	for (int i = 0; i < bearTraps.size(); i++)
	{
		//trap->Initialize();
		XMFLOAT3 tmp;
		tmp.x = rand() % 22 + 3.0f;
		tmp.y = 5;
		tmp.z = rand() % 22 + 3.0f;
		XMFLOAT3 pos = { tmp.x,tmp.y,tmp.z };
		bearTraps.at(i)->Initialize(pos, bearTraps.at(i)->GetRotation());
	}

}		



void Scene::Release()
{
	enemySpawn->Release();
	//trap->Release();
}

void Scene::Update(double deltaTime)
{

	for (int i = 0; i < fireTraps.size(); i++)
	{
		//fireTraps.at(i)->GetPosition();
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
		//bearTraps.at(i)->GetPosition();
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
//	trap->Update(deltaTime);
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
	//trap->Render();
	
}

void Scene::load()
{

}
