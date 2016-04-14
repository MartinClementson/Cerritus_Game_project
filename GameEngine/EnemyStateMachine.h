#pragma once
#include "IdleState.h"
#include "EnemyDeathState.h"
#include "AttackState.h"
class EnemyStateMachine
{
public:
	EnemyStateMachine();
	~EnemyStateMachine();
	void Initialize();
	void Release();
	void Update(double deltaTime);
private:
	IdleState* idleState;
	AttackState* attackState;
	EnemyDeathState deathState;
	//EnemyState activeState;//enum
};

