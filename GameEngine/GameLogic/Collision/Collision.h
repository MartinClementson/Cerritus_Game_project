#pragma once
#include "../../Source/LibIncluder.h"
#include "../Character/Enemy/Enemy.h"
#include "../Character/Player/Player.h"

using namespace std;
using namespace DirectX;

class Collision
{
private:
	XMFLOAT3 enemyPos;
	float enemyRad;
	vector<Enemy*> enemyBox;
	Player* player;
	bool enemyInit;
private:
	
	Collision();

public:
	//Collision(float radius);
	//Collision(XMFLOAT3 center, float radius);

	void AddEnemy(Enemy* enemy);
	void AddPlayer(Player* player);

	bool PlayerCollision(Enemy* enemy);
	bool ProjectileEnemyCollision(Projectile* projectile, Enemy* enemy);
	
	static Collision* GetInstance();

	~Collision();
};

