#include "Projectile.h"



Projectile::Projectile()
{
}

Projectile::Projectile(DirectX::XMFLOAT3 origin,DirectX::XMFLOAT3 direction)
{

	// hmm, i sense a disturbance in the force..

}


Projectile::~Projectile()
{

}

void Projectile::Initialize()
{
	position = { 0,0,0 };
	direction = { 0,0,0 };

	age = 0.0f;
	speed = 0.5f;
	dmgMultiplier = 2.0f;

	isFired = false;
	collided = false;
	
}

void Projectile::Release()
{

}

float Projectile::GetAge()
{
	return age;
}

float Projectile::GetSpeed()
{
	return speed;
}

DirectX::XMFLOAT3 Projectile::GetPos()
{
	return position;
}

DirectX::XMFLOAT3 Projectile::GetDir()
{
	return direction;
}

void Projectile::SetAge(float age)
{
	this->age = age;
}

void Projectile::SetPos(DirectX::XMFLOAT3 pos)
{
	this->position = pos;
}

