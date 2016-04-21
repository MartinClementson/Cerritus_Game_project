#pragma once
#include "../GameObject.h"
#include "../../../Character/Enemy/Enemy.h"
#include "../../../Collision/Collision.h"

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
	
	Collision* collision;
	XMFLOAT3 spawnPosition;
	
public:
	std::vector<Enemy*> Queue;
	std::vector<Enemy*> Alive;
	EnemySpawn();
	~EnemySpawn();

	void Release();
	void Initialize(XMFLOAT3 spawnPosition);
	void Render();

	void Update(double deltaTime);
	void InitEnemy();
	void SpawnEnemy();
};

