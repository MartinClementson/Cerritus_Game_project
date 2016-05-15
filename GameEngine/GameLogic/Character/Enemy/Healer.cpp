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
	if (movementSpeed != originalMovementSpeed)
	{
		slowTimer += (float)deltaTime;
	}
	if (slowTimer >= 2)
	{
		movementSpeed = originalMovementSpeed;
		slowTimer = 0.0f;
	}

	enemyStateMachine->Update(deltaTime);
	renderInfo.position = position;
	renderInfo.rotation = rotation;
	renderInfo.radius = radius;
}

void Healer::Initialize()
{
	this->charType = CharacterType::HEALER;
	movementSpeed = 5.0f;
	originalMovementSpeed = movementSpeed;
	health = 200;
	this->maxHealth = health;
	damage = 5.0f;
	rotation = { 0,0,90 };

	radius = 1.0f;
	radius2 = 2.0f;
	healing = 0;
	index = 0.0f;
	slowTimer = 0.0f;

	isAlive = false;
}

Healer::Healer(XMFLOAT3 spawn)
{
	this->position = spawn;

	Initialize();
	this->enemyStateMachine = new EnemyStateMachine();
	enemyStateMachine->Initialize();
	this->graphics = Graphics::GetInstance();
	renderInfo.position = position;
	renderInfo.rotation = rotation;
	renderInfo.radius = radius;
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
	renderInfo.position = position;
	renderInfo.rotation = rotation;
	renderInfo.radius = radius;
	renderInfo.render = true;
	if (this->health < (maxHealth * 0.95))
	{
		renderInfo.showHealthBar = true;
		renderInfo.normalizedHealthVal = health / maxHealth;
	}
	else
		renderInfo.showHealthBar = false;
	graphics->QueueRender(&renderInfo);
}

void Healer::Respawn(XMFLOAT3 spawn)
{
	this->position = spawn;
	this->isAlive = true;
	this->health = maxHealth;
	this->index = 0.0f;
	this->movementSpeed = 5.0f;
	this->GetStateMachine()->SetActiveState(EnemyState::ENEMY_ATTACK_STATE);
}

void Healer::Spawn(XMFLOAT3 spawn)
{
	this->position = spawn;
	this->isAlive = true;
	this->health = maxHealth;
	this->index = 0.0f;
	this->GetStateMachine()->SetActiveState(EnemyState::ENEMY_ATTACK_STATE);
}

void Healer::AIPattern(Player* player, double deltaTime)
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

CharacterType Healer::GetCharType()
{
	return this->charType;
}

void Healer::EnemyWithEnemyCollision(Healer* enemy, EnemyBase* enemys, double deltaTime)
{
	if (enemyStateMachine->GetActiveState() == ENEMY_ATTACK_STATE)
	{
		XMFLOAT3 enemyPos;
		XMFLOAT3 enemyPos2;
		Vec3 dir;

		enemyPos = enemy->GetPosition();
		enemyPos2 = enemys->GetPosition();

		dir.x = enemyPos.x - enemyPos2.x;
		dir.z = enemyPos.z - enemyPos2.z;

		dir.Normalize();

		enemys->position.x -= dir.x * (float)deltaTime * movementSpeed;
		enemys->position.z -= dir.z * (float)deltaTime * movementSpeed;
	}
	else if (enemyStateMachine->GetActiveState() == ENEMY_IDLE_STATE)
	{

	}
	else if (enemyStateMachine->GetActiveState() == ENEMY_DEATH_STATE)
	{
		//here they go to die 
	}
}

void Healer::EnemyWithEnemyCollision(EnemyBase* enemy, Healer* enemys, double deltaTime)
{
	if (enemyStateMachine->GetActiveState() == ENEMY_ATTACK_STATE)
	{
		XMFLOAT3 enemyPos;
		XMFLOAT3 enemyPos2;
		Vec3 dir;

		enemyPos = enemy->GetPosition();
		enemyPos2 = enemys->GetPosition();

		dir.x = enemyPos.x - enemyPos2.x;
		dir.z = enemyPos.z - enemyPos2.z;

		dir.Normalize();

		enemys->position.x -= dir.x * (float)deltaTime * movementSpeed;
		enemys->position.z -= dir.z * (float)deltaTime * movementSpeed;
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

EnemyStateMachine* Healer::GetStateMachine()
{
	return this->enemyStateMachine;
}
