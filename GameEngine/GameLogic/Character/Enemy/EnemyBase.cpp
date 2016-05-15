#include "EnemyBase.h"

using namespace std;


void EnemyBase::Release()
{
}

CharacterType EnemyBase::GetCharType()
{
	return this->charType;
}

EnemyBase::EnemyBase()
{
}

EnemyStateMachine * EnemyBase::GetStateMachine()
{
	return nullptr;
}

void EnemyBase::AIPatternHeal(EnemyBase * player, double deltaTime)
{
}


EnemyBase::~EnemyBase()
{
	
}

void EnemyBase::Initialize()
{
}

void EnemyBase::Update(double deltaTime)
{
}

float EnemyBase::GetHealth()
{
	return 0.0f;
}

float EnemyBase::GetMaxHealth()
{
	return 0.0f;
}

void EnemyBase::SetClosestHealer(EnemyBase* healer)
{	
	
}

EnemyBase * EnemyBase::GetClosestHealer()
{
	return nullptr;
}

void EnemyBase::SetHealth(float health)
{

}

void EnemyBase::Render()
{

}

XMFLOAT3 EnemyBase::GetPosition()
{
	return XMFLOAT3();
}

void EnemyBase::SetPosition(XMFLOAT3 pos)
{

}

float EnemyBase::GetRadius()
{
	return 0.0f;
}

float EnemyBase::GetRadius2()
{
	return 0.0f;
}

void EnemyBase::AIPattern(Player * player, double deltaTime)
{

}

void EnemyBase::EnemyWithEnemyCollision(EnemyBase * enemy, EnemyBase * enemys, double deltaTime)
{
	enemy = enemys;
}

void EnemyBase::Respawn(XMFLOAT3 spawn)
{

}

void EnemyBase::Spawn(XMFLOAT3 spawn)
{

}
