#pragma once
#include "../Character.h"
#include "../../../Source//LibIncluder.h"
#include "../../../Enumerations/Enumerations.h"
#include "../../InputHandler/Input/Input.h"
#include "../../../../GameEngine/Structs/RenderInfo.h"
#include "../Enemy/Enemy.h"
#include "../../StateMachines/EnemyStateMachine/EnemyStateMachine.h"

class Enemy :
	public Character
{
protected:

	float movementSpeed, health, damage;
private:
	RenderInfoEnemy renderInfo;
	EnemyStateMachine* enemyStateMachine;
private:
	void Release();
public:
	Enemy(XMFLOAT3 spawn);
	Enemy();
	virtual ~Enemy();

	void Initialize(XMFLOAT3 position);

	void Update(double deltaTime);

	void UpdateAttack(double deltaTime);
	void UpdateIdle(double deltaTime);
	void UpdateDead(double deltaTime);

	void Render();
};

