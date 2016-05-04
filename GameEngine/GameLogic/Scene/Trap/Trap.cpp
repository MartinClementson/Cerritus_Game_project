#include "Trap.h"



Trap::Trap()
{

}
Trap::~Trap()
{


}

void Trap::Initialize()
{
	damage = 25.0f;
	initTrap();
	
}
void Trap::Release()
{

}
void Trap::Update(double deltaTime)
{
	renderInfo.position = position;
	renderInfo.rotation = rotation;
	renderInfo.radius = radius;
	renderInfo.render = true;
}

void Trap::Render()
{
	grapichs = Graphics::GetInstance();	
}

float Trap::GetDamage()
{
	return damage;
}

void Trap::SetDamage(float damage)
{
	this->damage = damage;
}

XMFLOAT3 Trap::GetPosition()
{
	return this->position;
}

XMFLOAT3 Trap::GetRotation()
{
	return this->rotation;
}

void Trap::SetPosition(DirectX::XMFLOAT3 position)
{
	this->position = position;
}

void Trap::SetRotation(DirectX::XMFLOAT3 rotation)
{
	this->rotation = rotation;
}

void Trap::initTrap()
{
	
	int randomSpawn = rand() % 2 + 1;

	if (randomSpawn == 1)
	{
		float spawnX = rand() % 20 + 1.0f;
		float spawnZ = rand() % 20 + 1.0f;

		position.x = spawnX;
		position.y = 0;
		position.z = spawnZ;
	}
	if (randomSpawn == 2)
	{
		float spawnX = rand() % 32 + 1.0f;
		float spawnZ = rand() % 32 + 1.0f;

		position.x = spawnX;
		position.y = 2;
		position.z = spawnZ;
	}

}
