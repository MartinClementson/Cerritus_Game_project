#include "AttackState.h"



AttackState::AttackState()
{

}


AttackState::~AttackState()
{

}

void AttackState::Initialize()
{
	
}

void AttackState::Release()
{

}

void AttackState::Update(double deltaTime)
{
	enemy->UpdateAttack(deltaTime);
}

void AttackState::AIPattern()
{
	//shizzle
}

void AttackState::OnEnter()
{

}

void AttackState::OnExit()
{

}
