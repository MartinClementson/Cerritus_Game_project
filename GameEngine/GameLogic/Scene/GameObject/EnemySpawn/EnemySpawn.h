#pragma once
#include "../GameObject.h"
#include "../../../Character/Enemy/Enemy.h"

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

class EnemySpawn :
	public GameObject
{
private:
	Graphics* graphics;

	//std::vector<Enemy*> enemies;
private:
	

	std::vector<Enemy*> Queue;
	std::vector<Enemy*> Alive;
public:
	EnemySpawn();
	~EnemySpawn();

	void Release();
	void Initialize();
	void Render();

	void Update(double deltaTime);
	void InitEnemy();
	void SpawnEnemy();
};

