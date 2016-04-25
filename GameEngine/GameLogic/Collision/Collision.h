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
	XMFLOAT3 enemyPos, enemyPos2;
	float enemyRad, enemyRad2;
	XMFLOAT3 trapPos;
	float trapRad;
	XMFLOAT3 dir;
	
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

	bool BearTrapPlayerCollision(BearTrap * trap);
	bool BearTrapEnemyCollision(BearTrap * trap, Enemy *enemy);

	bool FireTrapPlayerCollision(FireTrap* trap);
	bool FireTrapEnemyCollision(FireTrap* trap, Enemy * enemy);


	bool PlayerCollision(Enemy* enemy);
	bool PlayerDistanceCollision(Enemy * enemy);
	bool ProjectileEnemyCollision(Projectile* projectile, Enemy* enemy);

	bool EnemyCollision(Enemy * enemy, Enemy* enemys);
	
	static Collision* GetInstance();

	bool TrapandEnemyLottery(BearTrap * trap, Enemy * enemys);

	~Collision();
};

