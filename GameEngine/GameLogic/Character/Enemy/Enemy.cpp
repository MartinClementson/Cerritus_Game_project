#include "Enemy.h"

Enemy::Enemy(XMFLOAT3 spawn)
{
	this->position = spawn;
	movementSpeed;
}

Enemy::Enemy()
{

}

Enemy::~Enemy()
{

}

void Enemy::Initialize(XMFLOAT3 position)
{
	graphics = Graphics::GetInstance();
	movementSpeed = 1.0f;

	health = 100.0f;

	damage = 22.0f;
	rotation = { 0,0,0 }; 
	
	dead = false;
	idle = false;
	active = true;
}

void Enemy::Release()
{
	
}

void Enemy::UpdateAttack(double deltaTime)
{
	//enemy basic movement
	//position of the enemy to test the movement of the enemy we set the start value at 0,0,0 and if the x value is 0 we move in that direction untill we reach x = 5 then we tail backwards to zero,
	//just to see if the movement of the enemies work. 
#pragma region movement

	if (position.x < 5)
	{
		position.x = position.x + movementSpeed;
	}
	else
	{
		position.x = 0;
	}
	//just if we want to decrease the movement speed of the enemys when they are hurt. 
	//if (health == 100)
	//{
	//	movementSpeed = 1.0f;
	//}
	//else if (health < 50)
	//{
	//	movementSpeed = 0.75f;
	//}
	//if (health == 0)
	//{
	//	//call for deathstate for the enemy..
	//}	
	//moving the enemy in the x coords with the speed of the enemy
#pragma endregion
	
	renderInfo = { position, rotation };
}
void Enemy::UpdateDead(double deltaTime)
{
	position.x = 0;
	position.z = 0;

	rotation.x = 0;
	rotation.y = 0;
	rotation.z = 0;
	
	//Remove enemy from game and move to back of queue
	//Trigger animation. Animation.death(true);

	bool dead = true;
	DeadBool(dead);

	renderInfo = { position, rotation };
}

bool Enemy::DeadBool(bool dead)
{
	dead = dead;

	return dead;
}

void Enemy::UpdateIdle(double deltaTime)
{
	position.x = 0;
	position.z = 0;

	rotation.x = 0;
	rotation.y = 0;
	rotation.z = 0;

	//If game gets paused put enemies in a idle state where position and rotation is
	// set to 0 
	renderInfo = { position, rotation };
}


void Enemy::Render()
{
	//graphics->QueueRender(renderInfo); doesnt work atm.
}
