#pragma once
#include "./EnemyBase.h"
class Healer :
	public EnemyBase
{
public:
	~Healer();

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

	
	void AIPattern(Player* player, double deltaTime);

	CharacterType GetCharType();
	
	void EnemyWithEnemyCollision(Healer * enemy, EnemyBase * enemys, double deltaTime);
	void EnemyWithEnemyCollision(EnemyBase * enemy, Healer * enemys, double deltaTime);
	void Release();

	EnemyStateMachine * GetStateMachine();

private:
	RenderInfoEnemy renderInfo;
	EnemyStateMachine* enemyStateMachine;
	Player * player;
	Healer();
};

