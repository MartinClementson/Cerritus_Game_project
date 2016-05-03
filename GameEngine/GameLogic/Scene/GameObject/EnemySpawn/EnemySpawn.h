#pragma once
#include "../GameObject.h"
#include "../../../Character/Enemy/Enemy.h"
#include "../../../Collision/Collision.h"
#include "../../../Character/Enemy/Healer.h"

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
	unsigned int waveAmount;
	Collision* collision;
	XMFLOAT3 spawnPosition;
public:
	std::vector<EnemyBase*> StandardQueue;
	std::vector<EnemyBase*> StandardAlive;

	std::vector<Enemy*> FastQueue;
	std::vector<Enemy*> FastAlive;
	EnemySpawn();
	~EnemySpawn();
	float spawnTimer;
	bool firstSpawn;

	void Release();
	void Initialize(XMFLOAT3 spawnPosition);
	void Render();

	void Update(double deltaTime);
	void InitEnemy();
	void SpawnEnemy();
	void RespawnEnemy();
	std::vector<EnemyBase*> GetStandardQueue();
	std::vector<EnemyBase*> GetStandardAlive();



};

