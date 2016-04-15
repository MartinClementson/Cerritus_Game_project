#pragma once
#include "LibIncluder.h"
#include "Model.h"
#include "Light.h"
#include "EnemySpawn.h"
#include "BearTrap.h"
#include "FireTrap.h"

class Scene
{
private:
	std::vector<Model>* sceneModels;
	std::vector<Light>* sceneLights;
	std::vector<EnemySpawn>* enemySpawns;
	std::vector<BearTrap>* bearTraps;
	std::vector<FireTrap>* fireTraps;

public:
	Scene();
	virtual ~Scene();
	void Initialize();
	void Release();
	void Update(double deltaTime);
	void Render();
	void load();
	//Collision();
};

