#pragma once
#include "../../Source/LibIncluder.h"
#include "GameObject/Model/Model.h"
#include "GameObject/Light/Light.h"
#include "GameObject/EnemySpawn/EnemySpawn.h"
#include "Trap/BearTrap/BearTrap.h"
#include "Trap/FireTrap/FireTrap.h"

class Scene
{
private:
	std::vector<Model>* sceneModels;
	std::vector<Light>* sceneLights;
	std::vector<EnemySpawn>* enemySpawns;
	std::vector<BearTrap*> bearTraps;
	std::vector<FireTrap*> fireTraps;

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

