#pragma once
#include "../../Source/LibIncluder.h"
#include "../../GameLogic/Character/Enemy/Enemy.h"

using namespace std;
using namespace DirectX;

class Collision
{
private:

private:
	vector<Enemy*> enemyBox;
	XMFLOAT3 center;
	float radius;
	Collision();

public:
	//Collision(float radius);
	//Collision(XMFLOAT3 center, float radius);

	void AddEnemy(Enemy* enemy);

	bool Collide();
	
	static Collision* GetInstance();

	~Collision();
};

