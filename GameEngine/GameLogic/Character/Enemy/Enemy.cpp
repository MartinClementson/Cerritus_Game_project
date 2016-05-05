#include "Enemy.h"

using namespace std;

EnemyStateMachine * Enemy::GetStateMachine()
{
	return this->enemyStateMachine;
}

Enemy::Enemy(XMFLOAT3 spawn, bool fast)
{
	this->position = spawn;
	this->fast = fast;
	this->Initialize();
	this->enemyStateMachine = new EnemyStateMachine();
	enemyStateMachine->Initialize();
	this->graphics = Graphics::GetInstance();
	renderInfo = { position, rotation };

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
	if (this->fast)
	{
		movementSpeed = 25.0f;
		originalMovementSpeed = movementSpeed;

		health = 50.0f;
		this->maxHealth = health;
		DoT = 0;
		damage = 5.0f;
		rotation = { 0,90,0 };

		radius = 1.0f;
		radius2 = 2.0f;

		DoTDur = 0;
		slowTimer = 0;
		index = 0.0f;

		isAlive = false;
	}
	else
	{
		movementSpeed = 18.0f;
		originalMovementSpeed = movementSpeed;
		health = 100.0f;
		this->maxHealth = health;
		DoT = 0;
		damage = 5.0f;
		rotation = { 0,0,0 };

		radius = 1.0f;
		radius2 = 2.0f;

		DoTDur = 0;
		slowTimer = 0;
		index = 0.0f;

		isAlive = false;
	}
}



void Enemy::Release()
{
	enemyStateMachine->Release();
}

void Enemy::Update(double deltaTime)
{                 
	
	health -= DoT;//deltaTime;

	if (health < maxHealth / 2 && closestHealer != nullptr)
	{
		GetStateMachine()->SetActiveState(ENEMY_HEAL_STATE);
	}
	else if (health < maxHealth / 2 && closestHealer == nullptr)
	{
		GetStateMachine()->SetActiveState(ENEMY_ATTACK_STATE);
	}


	if (GetStateMachine()->GetActiveState() == ENEMY_HEAL_STATE
		&&
		GetHealth() == GetMaxHealth())
	{
		GetStateMachine()->SetActiveState(ENEMY_ATTACK_STATE);
	}

	if (DoT != 0)
	{
		DoTDur += (float)deltaTime;
	}
	if (DoTDur >= 3)
	{
		DoT = 0;
		DoTDur = 0;
	}
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
	if (this->fast)
	{
		this->position = spawn;
		this->isAlive = true;
		this->health = maxHealth;
		this->DoT = 0.0f;
		this->index = 0.0f;
		this->GetStateMachine()->SetActiveState(EnemyState::ENEMY_ATTACK_STATE);
	}
	else
	{

		this->position = spawn;
		this->isAlive = true;
		this->health = maxHealth;
		this->DoT = 0.0f;
		this->index = 0.0f;
		this->GetStateMachine()->SetActiveState(EnemyState::ENEMY_ATTACK_STATE);
	}
}

float Enemy::GetMaxHealth()
{
	return this->maxHealth;
}

void Enemy::Spawn(XMFLOAT3 spawn)
{
	if (this->fast)
	{
		this->charType = CharacterType::FAST_ENEMY;
		this->position = spawn;
		this->isAlive = true;
		this->health = maxHealth;
		this->DoT = 0.0f;
		this->index = 0.0f;
		//this->GetStateMachine()->SetActiveState(EnemyState::ENEMY_IDLE_STATE);
	}
	else
	{
		this->charType = CharacterType::SLOW_ENEMY;
		this->position = spawn;
		this->isAlive = true;
		this->health = maxHealth;
		this->DoT = 0.0f;
		this->index = 0.0f;
		//this->GetStateMachine()->SetActiveState(EnemyState::ENEMY_IDLE_STATE);
	}
}

XMFLOAT3 Enemy::GetPosition() 
{ 
	return this->position; 
}

void Enemy::SetPosition(XMFLOAT3 pos)
{
	this->position = pos;
}

float Enemy::GetRadius() 
{
	return this->radius; 
}

void Enemy::AIPattern(Player* player, double deltaTime)
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
void Enemy::AIPatternHeal(EnemyBase* healer, double deltaTime)
{
	
	XMFLOAT3 playerPos = healer->GetPosition();
	Vec3 vect;

	vect.x = playerPos.x - GetPosition().x;
	vect.z = playerPos.z - GetPosition().z;

	vect.Normalize();

	//XMFLOAT3 temp = GetPosition();
	this->position.x += vect.x *(float)deltaTime * movementSpeed;
	this->position.z += vect.z *(float)deltaTime * movementSpeed;
	//SetPosition(temp);
}

CharacterType Enemy::GetCharType()
{
	return this->charType;
}
float Enemy::GetRadius2()
{
	return this->radius2;
}

void Enemy::EnemyWithEnemyCollision(Enemy* enemy, Enemy* enemys, double deltaTime)
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

void Enemy::SetClosestHealer(std::vector<EnemyBase*> healer)
{
	EnemyBase* tmpCloseHealer;

	XMFLOAT3 healPos;
	healPos.y = 0;
	XMFLOAT3 closest;
	closest.y = 0;
	XMFLOAT3 tmp;
	tmp.y = 0;
	bool first = false;

	if (healer.size() > 0)
	{
		for (size_t i = 0; i < healer.size(); i++)
		{
			healPos = healer.at(i)->position;

			//////////////////
			if (healer.at(i)->isAlive)
			{


				tmp.x = healPos.x - this->position.x;
				if (tmp.x < 0)
				{
					tmp.x = -tmp.x;
				}


				tmp.z = healPos.z - this->position.z;
				if (tmp.z < 0)
				{
					tmp.z = -tmp.z;
				}

				//////////////////

				if (first == false)
				{
					first = true;
					closest = tmp;
					tmpCloseHealer = healer.at(i);
				}
				else
				{
					if (closest.x > tmp.x && closest.z > tmp.z && healer.at(i)->isAlive)
					{
						closest = tmp;
						tmpCloseHealer = healer.at(i);
					}

				}
			}
			else
			{
				tmpCloseHealer = nullptr;
			}
			this->closestHealer = tmpCloseHealer;
		}
	}
	else
	{
		this->closestHealer = nullptr;
		
	}
}

EnemyBase* Enemy::GetClosestHealer()
{
	if (!closestHealer)
	{
		return nullptr;
	}
	else
	{
		return closestHealer;
	}
}
