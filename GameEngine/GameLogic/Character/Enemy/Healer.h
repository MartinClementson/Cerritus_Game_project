#pragma once
#include "./Enemy.h"
class Healer :
	public Enemy
{
public:
	virtual ~Healer();

	void Update(double deltaTime);
	void Initialize();
	Healer(XMFLOAT3 spawn);
	float GetHealth();
	void SetHealth(float health);
	XMFLOAT3 GetPosition();
	void SetPosition(XMFLOAT3 pos);
	float GetRadius();
	float GetRadius2();

	void Render();
	void Respawn(XMFLOAT3 spawn);
	void Spawn(XMFLOAT3 spawn);

	void AIPattern(Player * player, double deltaTime);

	void Release();

private:
	RenderInfoEnemy renderInfo;
	EnemyStateMachine* enemyStateMachine;
	Player * player;
	Healer();
};

