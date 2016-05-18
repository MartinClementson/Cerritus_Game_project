#pragma once
#include "../../Source/LibIncluder.h"
#include "../Character/Enemy/Enemy.h"
#include "../Character/Player/Player.h"
#include "../Scene/Trap/BearTrap/BearTrap.h"
#include "../Scene/Trap/FireTrap/FireTrap.h"
#include "../Scene/GameObject/Pickup/Pickup.h"

using namespace std;
using namespace DirectX;
struct SceneCollision
{
	XMFLOAT3 Pos;
	float Rad;
};
class Collision
{
private:
	XMFLOAT3 enemyPos, enemyPos2;
	float enemyRad, enemyRad2, enemyRad3;
	XMFLOAT3 trapPos;
	float trapRad;
	XMFLOAT3 dir;
	
	vector<EnemyBase*> enemyBox;
	vector<FireTrap*> fireTrap;
	vector<BearTrap*> bearTrap;
	vector<SceneCollision> SceneBoxesIn;
	vector<SceneCollision> SceneBoxesOut;
	Player* player;
	bool enemyInit;
private:
	Collision();
public:
	//Collision(float radius);
	//Collision(XMFLOAT3 center, float radius);

	void AddEnemy(EnemyBase* enemy);
	void AddPlayer(Player* player);
	void AddTrap(BearTrap* bTraps);
	void InitSceneCol();
	void ClearTraps();

	bool PlayerProxyTrap(BearTrap * trap);
	bool BearTrapActivation(BearTrap * trap);
	bool FireTrapActivation(FireTrap * trap);
	bool PlayerProxyEnemy(EnemyBase * enemy);
	bool HealerProximity(EnemyBase * enemy, EnemyBase * healer);
	bool Collision::EnemyProxTrap(BearTrap * trap, EnemyBase * enemy);

	bool BearTrapPlayerCollision(BearTrap * trap);
	bool BearTrapEnemyCollision(BearTrap * trap, EnemyBase *enemy);


	bool FireTrapPlayerCollision(FireTrap* trap);
	bool FireTrapEnemyCollision(FireTrap* trap, EnemyBase * enemy);


	bool SceneColIn(double deltaTime);
	bool SceneColIn(double deltaTime, EnemyBase * enemy);
	bool PlayerCollision(EnemyBase* enemy);
	bool PlayerDistanceCollision(EnemyBase * enemy);
	bool ProjectileEnemyCollision(Projectile* projectile, EnemyBase* enemy);


	Player* GetPlayer();

	bool EnemyCollision(EnemyBase * enemy, EnemyBase* enemys);

	
	static Collision* GetInstance();

	bool TrapandEnemyLottery(EnemyBase * enemys);

	bool WeaponPickupCollision(Pickup * pickup);

	~Collision();
};

