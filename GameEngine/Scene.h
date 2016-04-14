#pragma once
#include "LibIncluder.h"

class Scene
{
private:
	//std::vector<Model>* sceneModels;
	//std::vector<lights>* sceneLights;
	//std::vector<EnemySpawner>* enemySpawn;
	//std::vector<BearTrap>* bearTraps;
	//std::vector<FireTrap>* fireTraps;

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

