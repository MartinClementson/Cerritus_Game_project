#include "EnemyStateMachine.h"



EnemyStateMachine::EnemyStateMachine()
{
	this->idleState = new EnemyIdleState();
	this->attackState = new AttackState();
	this->deathState = new EnemyDeathState();
}

EnemyStateMachine::~EnemyStateMachine()
{
	delete idleState;
	delete attackState;
	delete deathState;
}

void EnemyStateMachine::Initialize()
{
	this->idleState->Initialize();
	this->attackState->Initialize();
	this->deathState->Initialize();
}

void EnemyStateMachine::Release()
{

}

void EnemyStateMachine::Update(double deltaTime)
{
	this->idleState->Update(deltaTime);
	this->attackState->Update(deltaTime);
	this->deathState->Update(deltaTime);
}
