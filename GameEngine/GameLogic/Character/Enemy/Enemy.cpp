#include "Enemy.h"

Enemy::Enemy()
{

}


Enemy::~Enemy()
{

}

void Enemy::Initialize()
{
	graphics = Graphics::GetInstance();
	movementSpeed = 1.0f;

	health = 100.0f;

	damage = 22.0f;
	position = { 0,0,0 };
	rotation = { 0,0,0 };

}

void Enemy::Release()
{
	
}

void Enemy::Update(double deltaTime)
{
	//enemy basic movement
	//position of the enemy to test the movement of the enemy we set the start value at 0,0,0 and if the x value is 0 we move in that direction untill we reach x = 5 then we tail backwards to zero,
	//just to see if the movement of the enemys work. 
	if (position.x == 0)
	{
		position.x = position.x + movementSpeed;
	}
	if (position.x == 5)
	{
		position.x = position.x - movementSpeed;
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
	
	renderInfo = { position, rotation };
}

void Enemy::Render()
{
	//graphics->QueueRender(renderInfo); doesnt work atm.
}
