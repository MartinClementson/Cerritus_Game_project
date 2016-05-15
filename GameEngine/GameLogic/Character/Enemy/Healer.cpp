#include "./Healer.h"

inline float get_degrees(float radian)
{

	return (radian * 180) / XM_PI;
}



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
	health = 300;
	this->maxHealth = health;
	damage = 5.0f;
	rotation = { 0,0,0 };
	
	RandNewDirection();

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
#pragma region Calculate  rotation of mesh

	Vec3 tempDir = Vec3(direction);
	tempDir.Normalize();
	XMVECTOR meshDirection = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	XMVECTOR enemyDirection = XMVectorSet(tempDir.x, 0.0f, tempDir.z, 0.0f);

	//Calculate angle between meshDir and shotDir
	float cosAngle = XMVector3Dot(enemyDirection, meshDirection).m128_f32[0];
	float angle = acos(cosAngle);
	float degrees = get_degrees(angle);
	////////////////////////////////////////////////////

	if (tempDir.x < 0)
		degrees = -degrees;

	rotation.y = degrees;


#pragma endregion
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
	RandNewDirection();
	this->isAlive = true;
	this->health = maxHealth;
	this->index = 0.0f;
	this->movementSpeed = 5.0f;
	this->GetStateMachine()->SetActiveState(EnemyState::ENEMY_ATTACK_STATE);
}

void Healer::Spawn(XMFLOAT3 spawn)
{
	this->position = spawn;
	RandNewDirection();
	this->isAlive = true;
	this->health = maxHealth;
	this->index = 0.0f;
	this->GetStateMachine()->SetActiveState(EnemyState::ENEMY_ATTACK_STATE);
}

void Healer::RandNewDirection()
{
	//int randoms = rand() % 15;
	//Randomize new  direction

	//roll if the randomized value is negative or positive
	int negativeRoll = rand() % 10 +1;
	if (negativeRoll <= 5)
		negativeRoll = -1;
	else
		negativeRoll = 1;

	//roll for x
	direction.x = GetPosition().x + (rand() % 30 +5) *negativeRoll;

	//roll if the randomized value is negative or positive
	negativeRoll = rand() % 10 +1;
	if (negativeRoll <= 5)
		negativeRoll = -1;
	else
		negativeRoll = 1;

	//roll for z
	direction.z = GetPosition().z + (rand() % 30 + 5) *negativeRoll;


}

void Healer::AIPattern(Player* player, double deltaTime)
{
	if (enemyStateMachine->GetActiveState() == ENEMY_ATTACK_STATE)
	{
		//XMFLOAT3 playerPos = player->GetPosition();
		//vect.x = playerPos.x - GetPosition().x;
		//vect.z = playerPos.z - GetPosition().z; 

		Vec3 vect;
		vect.x = direction.x - GetPosition().x;
		vect.z = direction.z - GetPosition().z;

		if (vect.Length() < 0.2f) //if we reached the randomized target. Randomize a new one!
		{
			RandNewDirection();
		
			vect.x = direction.x - GetPosition().x;
			vect.z = direction.z - GetPosition().z;
		}
#pragma region fleeing pattern
		//if (vect.Length() < 50.0f) //if the player is close. move away from the player
		//{
		//	vect.x = -vect.x;
		//	vect.z = -vect.z;

		//	vect.Normalize();

		//	this->position.x += vect.x *(float)deltaTime * movementSpeed;
		//	this->position.z += vect.z *(float)deltaTime * movementSpeed;
		//}
		//else
		//{
		//	
		//	this->position.x += 0.0f;
		//	this->position.z += 0.0f;

		//}
#pragma endregion

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

		enemyPos  = enemy->GetPosition();
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
