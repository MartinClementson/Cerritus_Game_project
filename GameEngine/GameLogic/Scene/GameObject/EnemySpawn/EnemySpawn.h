#pragma once
#include "../GameObject.h"
#include "../../../Character/Enemy/Enemy.h"
#include "../../../Collision/Collision.h"
#include "../../../Scene/Waves/Waves.h"
#include "../../../Character/Enemy/Healer.h"

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

class EnemySpawn :
	public GameObject
{
private:
	Graphics* graphics;

	void killEnemy(int index);

	int nrOfAliveEnemies;
	//std::vector<Enemy*> enemies;
private:
	Collision* collision;
	XMFLOAT3 spawnPosition;
public:
	XMFLOAT3 spawn;
	XMFLOAT3 spawnPosInfo;
	Waves waves;
	int currentWave = 0;
	int enemyWaveAmount = 0;
	int waveAmount = 0;
	double waveTimer = 0;
	int intSpawn;

	int a = 0;
	bool fast = false;
	bool win = false;
	int GetNrAliveEnemies() { return this->nrOfAliveEnemies; }
	EnemyBase* Alive[100];

	EnemySpawn();
	~EnemySpawn();
	float spawnTimer;
	bool firstSpawn = false;

	void Release();
	void Initialize();
	//void GetEnemyInfo(int info);
	void Render();

	void Update(double deltaTime);
	void InitEnemy();

	void SpawnEnemy(int waveAmount);
	void RespawnEnemy(int i);

};

