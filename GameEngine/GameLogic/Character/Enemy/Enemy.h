#pragma once
#include "../Character.h"
#include "../../../Source//LibIncluder.h"
#include "../../../Enumerations/Enumerations.h"
#include "../../InputHandler/Input/Input.h"
#include "../../../../GameEngine/Structs/RenderInfo.h"
#include "../../StateMachines/EnemyStateMachine/EnemyStateMachine.h"
#include "../../../Structs/DataTypes.h"
#include "../Player/Player.h"

class Enemy :
	public Character
{
protected:

	float movementSpeed, health, damage;
private:
	RenderInfoEnemy renderInfo;
	EnemyStateMachine* enemyStateMachine;
	Player * player;
private:
	void Release();
	Enemy();
public:
	Enemy(XMFLOAT3 spawn);

	bool isAlive;

	virtual ~Enemy();

	void Initialize();

	void Update(double deltaTime);

	float GetHealth();

	void SetHealth(float health);

	void Render();
	XMFLOAT3 GetPosition();
	void SetPosition(XMFLOAT3 pos);
	float GetRadius();
	float GetRadius2();
	void AIPattern(Player * player, double deltaTime);
	void EnemyWithEnemyCollision(Enemy * enemy, Enemy * enemys, double deltaTime);
	void Respawn(XMFLOAT3 spawn);
};

