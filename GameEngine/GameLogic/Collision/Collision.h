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
	float enemyRad, enemyRad2, enemyRad3;
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
	void AddTrap(BearTrap* bTraps);
	void ClearTraps();

	bool PlayerProxyTrap(BearTrap * trap);
	bool PlayerProxyEnemy(Enemy * enemy);
	bool Collision::EnemyProxTrap(BearTrap * trap, Enemy * enemy);

	bool BearTrapPlayerCollision(BearTrap * trap);
	bool BearTrapEnemyCollision(BearTrap * trap, Enemy *enemy);


	bool FireTrapPlayerCollision(FireTrap* trap);
	bool FireTrapEnemyCollision(FireTrap* trap, Enemy * enemy);


	bool PlayerCollision(Enemy* enemy);
	bool PlayerDistanceCollision(Enemy * enemy);
	bool ProjectileEnemyCollision(Projectile* projectile, Enemy* enemy);


	Player* GetPlayer();

	bool EnemyCollision(Enemy * enemy, Enemy* enemys);

	
	static Collision* GetInstance();

	bool TrapandEnemyLottery(Enemy * enemys);

	~Collision();
};

