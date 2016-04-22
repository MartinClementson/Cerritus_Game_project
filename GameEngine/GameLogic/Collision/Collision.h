#pragma once
#include "../../Source/LibIncluder.h"
#include "../Character/Enemy/Enemy.h"
#include "../Character/Player/Player.h"
#include "../Scene/Trap/BearTrap/BearTrap.h"
#include"../Scene/Trap/FireTrap/FireTrap.h"
using namespace std;
using namespace DirectX;

class Collision
{
private:
	XMFLOAT3 enemyPos;
	float enemyRad;
	XMFLOAT3 trapPos;
	float trapRad;

	vector<Enemy*> enemyBox;
	vector<FireTrap*> fireTrap;
	vector<BearTrap*> bearTrap;
	Player* player;
	bool enemyInit;
private:
	
	Collision();

public:
	//Collision(float radius);
	//Collision(XMFLOAT3 center, float radius);

	void AddEnemy(Enemy* enemy);
	void AddPlayer(Player* player);
	void AddTrap(FireTrap* fTraps,BearTrap* bTraps);

	bool bearTrapPlayerCollision(BearTrap * trap);
	bool bearTrapEnemyCollision(Enemy *enemy);

	bool fireTrapPlayerCollision(FireTrap* trap);
	bool fireTrapEnemyCollision(FireTrap* trap, Enemy * enemy);


	bool PlayerCollision(Enemy* enemy);
	bool ProjectileEnemyCollision(Projectile* projectile, Enemy* enemy);
	
	static Collision* GetInstance();

	~Collision();
};

