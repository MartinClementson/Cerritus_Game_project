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


	Trap * trap;
	Collision* collision;
	int trapAmount;
	double RespawnTimer;


public:
	std::vector<BearTrap*> bearTraps;
	std::vector<FireTrap*> fireTraps;
	std::vector<EnemySpawn*> enemySpawns;
	Scene();
	virtual ~Scene();

	void Initialize();
	void InitFireTrap();
	void InitBearTrap();
	void Release();
	void Update(double deltaTime);
	void Render();
	void load();

	void EvadeTrap(Enemy * enemy, BearTrap * bear, double deltaTime);

	void AddEnemySpawn(XMFLOAT3 spawnPosition);
};