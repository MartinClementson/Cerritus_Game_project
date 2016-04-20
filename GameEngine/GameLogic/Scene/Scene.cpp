#include "Scene.h"



Scene::Scene()
{
	/*this->bearTraps = new std::vector<BearTrap>;
	this->fireTraps = new std::vector<FireTrap>;*/
}


Scene::~Scene()
{

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



void Scene::Release()
{

}

void Scene::Update(double deltaTime)
{

	for (int i = 0; i < fireTraps.size(); i++)
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
	for (int i = 0; i < bearTraps.size(); i++)
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

}

void Scene::Render()
{
	for (int i = 0; i < fireTraps.size(); i++)
	{
		fireTraps.at(i)->Render();
	}
	for (int i = 0; i < bearTraps.size(); i++)
	{
		bearTraps.at(i)->Render();
	}

}

void Scene::load()
{

}
