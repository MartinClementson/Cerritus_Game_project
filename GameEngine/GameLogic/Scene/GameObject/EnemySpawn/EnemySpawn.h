#pragma once
#include "../GameObject.h"
#include "../../../Character/Enemy/Enemy.h"
#include "../../../Collision/Collision.h"
#include "../../GameLogic/Scene/Waves/Waves.h"

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
	XMFLOAT3 spawn;
	Waves waves;
	int currentWave = 1;
	int enemyWaveAmount = 0;
	int waveAmount = 0;
	double waveTimer = 0;
	int intSpawn;

	int a = 0;


	std::vector<Enemy*> Queue;
	std::vector<Enemy*> Alive;
	EnemySpawn();
	~EnemySpawn();
	float spawnTimer;
	bool firstSpawn;

	void Release();
	void Initialize();
	//void GetEnemyInfo(int info);
	void Render();

	void Update(double deltaTime);
	void InitEnemy();
	void SpawnEnemy();
	void RespawnEnemy(int i);
};

