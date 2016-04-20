#include "EnemyStateMachine.h"



EnemyStateMachine::EnemyStateMachine()
{
	//this->idleState = new EnemyIdleState();
	//this->attackState = new AttackState();
	//this->deathState = new EnemyDeathState();
}

EnemyStateMachine::~EnemyStateMachine()
{
	//delete idleState;
	//delete attackState;
	//delete deathState;
}

void EnemyStateMachine::Initialize()
{
	//activeState = ENEMY_IDLE_STATE;
	//this->idleState->Initialize();
	//this->attackState->Initialize();
	//this->deathState->Initialize();
}

void EnemyStateMachine::Release()
{
	//this->idleState->Release();
	//this->attackState->Release();
	//this->deathState->Release();
}

void EnemyStateMachine::Update(double deltaTime)
{
	if (activeState == ENEMY_IDLE_STATE)
	{
		this->idleState->Update(deltaTime);

	}
	else if (activeState == ENEMY_ATTACK_STATE)
	{
		this->attackState->Update(deltaTime);

	}
	else if (activeState == ENEMY_DEATH_STATE)
	{
		this->deathState->Update(deltaTime);

	}
}
