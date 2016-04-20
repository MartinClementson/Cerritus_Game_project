#include "Scene.h"



Scene::Scene()
{

}


Scene::~Scene()
{
	delete this->sceneModels;
	delete this->sceneLights;
	delete this->enemySpawns;
	delete this->bearTraps;
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

}

void Scene::Render()
{

}

void Scene::load()
{

}
