#pragma once
#include "GameObject.h"
class EnemySpawn :
	public GameObject
{
public:
	EnemySpawn();
	~EnemySpawn();
	void Initialize();
	void Release();
	void Update(double deltaTime);
	void Render();
private:
	//std::vector<Enemy>* enemies;
};

