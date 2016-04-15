#pragma once
#include "EnemyDeathState.h"
#include "EnemyIdleState.h"
#include "AttackState.h"
#include "Enumerations.h"
class EnemyStateMachine
{
public:
	EnemyStateMachine();
	~EnemyStateMachine();
	void Initialize();
	void Release();
	void Update(double deltaTime);
private:
	EnemyIdleState* idleState;
	AttackState* attackState;
	EnemyDeathState deathState;
	EnemyState activeState;//enum
};

