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
	//std::vector<Enemy*> enemies;
private:
	void Release();
	void Initialize();

	std::vector<Enemy*> Queue;
	std::vector<Enemy*> Alive;
public:
	EnemySpawn();
	~EnemySpawn();

	void Update(double deltaTime);
	void MoveEnemyToPlay();
	void SpawnEnemy();
};

