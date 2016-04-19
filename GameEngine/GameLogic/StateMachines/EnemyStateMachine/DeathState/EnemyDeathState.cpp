#include "EnemyDeathState.h"



EnemyDeathState::EnemyDeathState()
{

}


EnemyDeathState::~EnemyDeathState()
{

}

void EnemyDeathState::Initialize()
{

}

void EnemyDeathState::Release()
{

}

void EnemyDeathState::Update(double deltaTime)
{
	enemy->UpdateDead(deltaTime);
}

void EnemyDeathState::AIPattern()
{

}

void EnemyDeathState::OnEnter()
{

}

void EnemyDeathState::OnExit()
{

}
