#pragma once
#include "./DeathState/EnemyDeathState.h"
#include "./IdleState/EnemyIdleState.h"
#include "./AttackState/AttackState.h"
#include "../../../Enumerations/Enumerations.h"
class EnemyStateMachine
{
private: // For variables.
	EnemyIdleState* idleState;
	AttackState* attackState;
	EnemyDeathState* deathState;
	EnemyState activeState;//enum
private: // For Functions

public:
	EnemyStateMachine();
	~EnemyStateMachine();
	void Initialize();
	void Release();
	void Update(double deltaTime);

};

