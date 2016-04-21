#pragma once
#include "../../Source/LibIncluder.h"
#include "../Character/Enemy/Enemy.h"
#include "../Character/Player/Player.h"

using namespace std;
using namespace DirectX;

class Collision
{
private:

private:
	vector<Enemy*> enemyBox;
	Player* player;
	XMFLOAT3 center;
	float radius;
	bool enemyInit;
	Collision();

public:
	//Collision(float radius);
	//Collision(XMFLOAT3 center, float radius);

	void AddEnemy(Enemy* enemy, int index, int listCapacity);
	void RemoveEnemy(int index);
	void AddPlayer(Player* player);

	bool Collide();
	
	static Collision* GetInstance();

	~Collision();
};

