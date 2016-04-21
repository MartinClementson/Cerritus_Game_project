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
	

	//this->position.x = rand() % 10 + 1;
	//this->position.z = rand() % 10 + 1;
	//this->position.y = rand() % 10 + 1;
	renderInfo = { position,rotation }; // need to think about how the dmg is deliverd over the enemys which collided with the trap. 

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
DirectX::XMFLOAT3 Trap::GetPosition()
{
	return this->position;
}
DirectX::XMFLOAT3 Trap::GetRotation()
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
