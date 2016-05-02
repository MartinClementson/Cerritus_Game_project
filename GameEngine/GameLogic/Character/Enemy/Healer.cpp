#include "./Healer.h"



Healer::Healer()
{

}


Healer::~Healer()
{
	delete enemyStateMachine;
}

void Healer::Update(double deltaTime)
{
	enemyStateMachine->Update(deltaTime);
	renderInfo = { position, rotation };
}

void Healer::Initialize()
{
	movementSpeed = 5.0f;
	health = 300;
	damage = 5.0f;
	rotation = { 0,0,90 };

	radius = 1.0f;
	radius2 = 2.0f;

	index = 0.0f;

	isAlive = false;
}

Healer::Healer(XMFLOAT3 spawn)
{
	this->position = spawn;
	Initialize();
	this->enemyStateMachine = new EnemyStateMachine();
	enemyStateMachine->Initialize();
	this->graphics = Graphics::GetInstance();
}

float Healer::GetHealth()
{
	return health;
}

void Healer::SetHealth(float health)
{
	this->health = health;
}

XMFLOAT3 Healer::GetPosition()
{
	return this->position;
}

void Healer::SetPosition(XMFLOAT3 pos)
{
	this->position = pos;
}

float Healer::GetRadius()
{
	return radius;
}

float Healer::GetRadius2()
{
	return radius2;
}

void Healer::Render()
{
	renderInfo = { position, rotation };
	graphics->QueueRender(&renderInfo);
}

void Healer::Respawn(XMFLOAT3 spawn)
{
	this->position = spawn;
	this->isAlive = true;
	this->health = 300.0f;
	this->DoT = 0.0f;
	this->index = 0.0f;
	this->GetStateMachine()->SetActiveState(EnemyState::ENEMY_ATTACK_STATE);
}

void Healer::Spawn(XMFLOAT3 spawn)
{
	this->position = spawn;
	this->isAlive = true;
	this->health = 300.0f;
	this->DoT = 0.0f;
	this->index = 0.0f;
	this->GetStateMachine()->SetActiveState(EnemyState::ENEMY_IDLE_STATE);
}

void Healer::AIPattern(Player * player, double deltaTime)
{
	if (enemyStateMachine->GetActiveState() == ENEMY_ATTACK_STATE)
	{
		XMFLOAT3 playerPos = player->GetPosition();
		Vec3 vect;

		vect.x = playerPos.x - GetPosition().x;
		vect.z = playerPos.z - GetPosition().z;

		vect.Normalize();

		//XMFLOAT3 temp = GetPosition();
		this->position.x += vect.x *(float)deltaTime * movementSpeed;
		this->position.z += vect.z *(float)deltaTime * movementSpeed;
		//SetPosition(temp);

	}
	else if (enemyStateMachine->GetActiveState() == ENEMY_IDLE_STATE)
	{

	}
	else if (enemyStateMachine->GetActiveState() == ENEMY_DEATH_STATE)
	{
		//here they go to die 
	}
}



void Healer::Release()
{
}
