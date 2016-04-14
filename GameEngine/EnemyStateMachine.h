#pragma once
#include "IdleState.h"
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
	//AttackState* attackState;
	//DeathState deathState;
	//EnemyState activeState;//enum
};

