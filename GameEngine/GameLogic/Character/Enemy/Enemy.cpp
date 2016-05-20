#include "Enemy.h"

using namespace std;
inline float get_degrees(float radian)
{

	return (radian * 180) / XM_PI;
}

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
	this->animation = EnemyAnimations::ENEMY_WALK;
	this->animationTime = 0.0f;
	renderInfo.position = position;
	renderInfo.rotation = rotation;
	renderInfo.radius = radius;
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
	closestHealer = nullptr;
	graphics = Graphics::GetInstance();
	this->deathAnim = false;
	this->timeToDie = false;
		
	//EnemyBase::Initialize();
	

	if (this->fast)
	{
		this->healable = true;
		movementSpeed = 22.0f;
		originalMovementSpeed = movementSpeed;

		health = 75.0f;
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
		this->healable = false;
		movementSpeed = 18.0f;
		originalMovementSpeed = movementSpeed;
		health = 200.0f;
		this->maxHealth = health;
		DoT = 0;
		damage = 5.0f;
		rotation = { 0,0,0 };

		radius = 2.0f;
		radius2 = 3.0f;

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


	health -= DoT * 25 * (float)deltaTime;


	if (health < (maxHealth / 1.5) && closestHealer && this->healable != false)
	{
		enemyStateMachine->SetActiveState(ENEMY_HEAL_STATE);
	}
	else if (health >= maxHealth)
	{
		GetStateMachine()->SetActiveState(ENEMY_ATTACK_STATE);
	}

	if (health < maxHealth / 2 && !closestHealer)
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

	if (movementSpeed == 0 && slowTimer >= 0.7f)
	{
		movementSpeed = originalMovementSpeed;
		slowTimer = 0.0f;
	}
	if (movementSpeed != originalMovementSpeed)
	{
		slowTimer += (float)deltaTime;
	}
	if (slowTimer >= 2.0f)
	{
		movementSpeed = originalMovementSpeed;
		slowTimer = 0.0f;
	}
	enemyStateMachine->Update(deltaTime);

#pragma region Calculate rotation of mesh


	XMVECTOR meshDirection = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	XMVECTOR enemyDirection = XMVectorSet(direction.x, 0.0f, direction.z, 0.0f);

	//Calculate angle between meshDir and enemyDir
	float cosAngle = XMVector3Dot(enemyDirection, meshDirection).m128_f32[0];
	float angle = acos(cosAngle);
	float degrees = get_degrees(angle);

	if (direction.x < 0)
		degrees = -degrees;

	rotation.y = degrees;


#pragma endregion

	

	if (this->animationTime >= 0.9f)
	{
		this->animationTime = 0.00f;
		if (this->animation == EnemyAnimations::ENEMY_ATTACK)
		{
			this->animation = EnemyAnimations::ENEMY_WALK;
		}
		else if (this->animation == EnemyAnimations::ENEMY_DIE)
		{
			this->timeToDie = true;
		}
	}

	if (deathAnim && this->animation != EnemyAnimations::ENEMY_DIE)
	{
		this->animation = EnemyAnimations::ENEMY_DIE;
		this->animationTime = 0.00f;
	}

	if (this->animation == EnemyAnimations::ENEMY_ATTACK)
	{
		this->animationTime += animationSpeed * 20.0f;
	}
	else if(this->animation == EnemyAnimations::ENEMY_WALK)
	{
		this->animationTime += animationSpeed * movementSpeed ;
	}
	else if (this->animation == EnemyAnimations::ENEMY_DIE)
	{
		this->animationTime += animationSpeed * 5.0f;
	}

	renderInfo.position = position;
	renderInfo.rotation = rotation;
	renderInfo.radius = radius;
}

float Enemy::GetHealth()
{
	return this->health;
}

void Enemy::SetHealth(float health)
{
	if (health > this->health)
		this->isBeingHealed = true;
	this->health		= health;
}

void Enemy::Render()
{
	renderInfo.object			= ENEMY_1;
	renderInfo.position			= position;
	renderInfo.enemyAnim		= this->animation;
	renderInfo.animationTime	= min(this->animationTime , 1.0f );
	renderInfo.rotation			= rotation;
	renderInfo.radius			= radius;
	renderInfo.render			= true;
	renderInfo.isBeingHealed	= this->isBeingHealed;

	if (this->health < (maxHealth * 0.95))
	{
		renderInfo.showHealthBar = true;
		renderInfo.normalizedHealthVal = health / maxHealth;
	}
	else
		renderInfo.showHealthBar = false;

#pragma region on fire rendering
	if (DoTDur > 0.0f)
	{
		renderInfo.isOnfire = true;
		renderInfo.showHealthBar = true;

	}
	else
	{
		renderInfo.isOnfire = false;
	}
#pragma endregion

	if (slowTimer > 0.0f)
	{
		//renderInfo.isSlowed = true;
		//renderInfo.showHealthBar = true;
	}
	else
		renderInfo.isSlowed = false;


	graphics->QueueRender(&renderInfo);
}

void Enemy::Respawn(XMFLOAT3 spawn)
{
	this->deathAnim = false;
	this->timeToDie = false;
	this->animation = EnemyAnimations::ENEMY_WALK;
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
	this->position = spawn;
	this->isAlive = true;
	this->DoT = 0.0f;
	this->index = 0.0f;
	this->GetStateMachine()->SetActiveState(EnemyState::ENEMY_ATTACK_STATE);
	this->deathAnim = false;
	this->animation = EnemyAnimations::ENEMY_WALK;
	this->timeToDie = false;
	
	

	if (this->fast) //kolla in här sen
	{
		this->charType = CharacterType::FAST_ENEMY;
		this->position = spawn;
		this->isAlive = true;
		this->health = maxHealth;
		this->DoT = 0.0f;
		this->index = 0.0f;
		//this->GetStateMachine()->SetActiveState(EnemyState::ENEMY_HEAL_STATE);
	}
	else
	{
		this->charType = CharacterType::SLOW_ENEMY;
		this->position = spawn;
		this->isAlive = true;
		this->health = maxHealth;
		this->DoT = 0.0f;
		this->index = 0.0f;
		//this->GetStateMachine()->SetActiveState(EnemyState::ENEMY_HEAL_STATE);
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
	
	if (enemyStateMachine->GetActiveState() == ENEMY_ATTACK_STATE || enemyStateMachine->GetActiveState() == ENEMY_HEAL_STATE)
	{
		
		XMFLOAT3 playerPos = player->GetPosition();
		

		direction.x = playerPos.x - GetPosition().x;
		direction.z = playerPos.z - GetPosition().z;

		if (direction.Length() > 1)
		{
			direction.Normalize();

			this->position.x += direction.x *(float)deltaTime * movementSpeed;
			this->position.z += direction.z *(float)deltaTime * movementSpeed;
		}
		else
		{
			direction.Normalize();
			this->position = this->position;
		}
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
	if (enemyStateMachine->GetActiveState() == ENEMY_HEAL_STATE)
	{
		XMFLOAT3 healerPos = healer->GetPosition();
		

		direction.x = healerPos.x - GetPosition().x;
		direction.z = healerPos.z - GetPosition().z;

		if (direction.Length() > 6)
		{
			direction.Normalize();

			this->position.x += direction.x *(float)deltaTime * movementSpeed;
			this->position.z += direction.z *(float)deltaTime * movementSpeed;
		}
		else
		{
			direction.Normalize();
			this->position = this->position;
		}
	}
	else if (enemyStateMachine->GetActiveState() == ENEMY_IDLE_STATE)
	{
		
	}
	else if (enemyStateMachine->GetActiveState() == ENEMY_ATTACK_STATE)
	{
		
	}
	else if (enemyStateMachine->GetActiveState() == ENEMY_DEATH_STATE)
	{
		//here they go to die 
	}
}

CharacterType Enemy::GetCharType()
{
	return this->charType;
}

float Enemy::GetRadius2()
{
	return this->radius2;
}

void Enemy::EnemyWithEnemyCollision(EnemyBase* enemy, EnemyBase* enemys, double deltaTime)
{
	if (enemyStateMachine->GetActiveState() == ENEMY_ATTACK_STATE || enemyStateMachine->GetActiveState() == ENEMY_HEAL_STATE)
	{
		XMFLOAT3 enemyPos;
		XMFLOAT3 enemyPos2;
		Vec3 dir;

		enemyPos = enemy->GetPosition();
		enemyPos2 = enemys->GetPosition();

		dir.x = enemyPos.x - enemyPos2.x;
		dir.z = enemyPos.z - enemyPos2.z;

		dir.Normalize();

		if (enemys->deathAnim)
		{
			enemy->position.x += dir.x * (float)deltaTime * movementSpeed;
			enemy->position.z += dir.z * (float)deltaTime * movementSpeed;
		}
		else if (enemy->deathAnim)
		{
			enemys->position.x -= dir.x * (float)deltaTime * movementSpeed;
			enemys->position.z -= dir.z * (float)deltaTime * movementSpeed;
		}
		else
		{
			enemys->position.x -= dir.x * (float)deltaTime * movementSpeed;
			enemys->position.z -= dir.z * (float)deltaTime * movementSpeed;
		}
		
	}
	else if (enemyStateMachine->GetActiveState() == ENEMY_IDLE_STATE)
	{

	}
	else if (enemyStateMachine->GetActiveState() == ENEMY_DEATH_STATE)
	{
		//here they go to die 
	}
}

void Enemy::SetClosestHealer(EnemyBase* healer)
{
	this->closestHealer = healer;
}

EnemyBase* Enemy::GetClosestHealer()
{
	return closestHealer;
}


