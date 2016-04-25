#include "Enemy.h"

Enemy::Enemy(XMFLOAT3 spawn)
{
	this->position = spawn;
	Initialize();
	this->enemyStateMachine = new EnemyStateMachine();
	this->graphics = Graphics::GetInstance();

}

Enemy::Enemy()
{
	
}

Enemy::~Enemy()
{
	delete enemyStateMachine;
}

void Enemy::Initialize()
{
	graphics = Graphics::GetInstance();
	movementSpeed = 20.0f;

	health = 100.0f;
	DoT = 0;
	damage = 22.0f;
	rotation = { 0,0,0 }; 
	
	radius = 0.5f;
	radius2 = 6.0f;

	DoTDur = 0;
	slowTimer = 0; 

	isAlive = false;
}

void Enemy::Release()
{
	enemyStateMachine->Release();
}

void Enemy::Update(double deltaTime)
{
	health -= DoT;//deltaTime;

	if (DoT != 0)
	{
		DoTDur += deltaTime;
	}
	if (DoTDur >= 3)
	{
		DoT = 0;
		DoTDur = 0;
	}
	if (movementSpeed != 20.0f)
	{
		slowTimer += deltaTime;
	}
	if (slowTimer >= 3)
	{
		movementSpeed = 20.0f;
		slowTimer = 0.0f; 
	}
	enemyStateMachine->Update(deltaTime);
	renderInfo = { position, rotation };
}

float Enemy::GetHealth()
{
	return this->health;
}

void Enemy::SetHealth(float health)
{
	this->health = health;
}

void Enemy::Render()
{
	renderInfo = { position, rotation };
	graphics->QueueRender(&renderInfo);
}

void Enemy::Respawn(XMFLOAT3 spawn)
{
	this->position = spawn;
	this->isAlive  = true;
	this->health = 100.0f;
	this->DoT = 0.0f;
}

XMFLOAT3 Enemy::GetPosition() 
{ 
	return this->position; 
}

void Enemy::SetPosition(XMFLOAT3 pos)
{
	pos = position;
}

float Enemy::GetRadius() 
{
	return this->radius; 
}

float Enemy::GetRadius2()
{
	return this->radius2;
}

void Enemy::AIPattern(Player * player, double deltaTime)
{
	XMFLOAT3 playerPos = player->GetPosition();
	Vec3 vect;

	vect.x = playerPos.x - position.x;
	vect.z = playerPos.z - position.z;
		
	vect.Normalize();

	this->position.x +=  vect.x *(float)deltaTime * movementSpeed;
	this->position.z +=  vect.z *(float)deltaTime * movementSpeed;
}

void Enemy::EnemyWithEnemyCollision(Enemy* enemy, Enemy* enemys, double deltaTime)
{
	XMFLOAT3 enemyPos;
	XMFLOAT3 enemyPos2;
	Vec3 dir;

	enemyPos = enemy->GetPosition();
	enemyPos2 = enemys->GetPosition();

	dir.x = enemyPos.x - enemyPos2.x;
	dir.z = enemyPos.z - enemyPos2.z;

	this->position.x += dir.x * (float)deltaTime;
	this->position.z += dir.z * (float)deltaTime;
}


