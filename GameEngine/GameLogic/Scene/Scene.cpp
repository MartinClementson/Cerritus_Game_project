#include "Scene.h"



Scene::Scene()
{

}


Scene::~Scene()
{
	delete this->bearTraps;
	delete this->enemySpawns;
	delete this->fireTraps;
}

void Scene::Initialize()
{

}

void Scene::Release()
{

}

void Scene::Update(double deltaTime)
{
	for (int i = 0; i < fireTraps->size(); i++)
	{
		fireTraps->at(i).GetPosition();
		fireTraps->at(i).Update(deltaTime);
		if (fireTraps->at(i).GetDot() == 0)
		{

		}
		else if (fireTraps->at(i).GetDot() > 0)
		{
			fireTraps->at(i).GetDamage();
		}	
		
	}
	for (int i = 0; i < bearTraps->size(); i++)
	{
		bearTraps->at(i).GetPosition();
		bearTraps->at(i).Update(deltaTime);
		if (bearTraps->at(i).GetSlow() == 0)
		{

		}
		else if (bearTraps->at(i).GetSlow() > 0)
		{
			bearTraps->at(i).GetDamage();
		}

		
	}
}

void Scene::Render()
{
	//skicka fire traps,beartraps och enemy spawn till render queue.
	//graphichs = renderqueue(beartraps)
	//graphichs = renderqueue(firetraps)
	//graphichs = renderqueue(enemyspawn)
}

void Scene::load()
{
	//load scene
}
