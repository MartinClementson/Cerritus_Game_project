#pragma once
#include "./DeathState/EnemyDeathState.h"
#include "./IdleState/EnemyIdleState.h"
#include "./AttackState/AttackState.h"
#include "./HealingState/HealingState.h"
#include "../../../Enumerations/Enumerations.h"
class EnemyStateMachine
{
private: // For variables.
	EnemyIdleState* idleState;
	AttackState* attackState;
	EnemyDeathState* deathState;
	HealingState* healingState;
	//enum
private: // For Functions

public:
	EnemyState activeState;
	EnemyState GetActiveState();
	void SetActiveState(EnemyState state);
	EnemyStateMachine();
	~EnemyStateMachine();
	void Initialize();
	void Release();
	void Update(double deltaTime);

};

