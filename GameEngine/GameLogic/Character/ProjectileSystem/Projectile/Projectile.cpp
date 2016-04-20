#include "Projectile.h"



Projectile::Projectile()
{
	isFired = false;
}

Projectile::Projectile(DirectX::XMFLOAT3 origin,DirectX::XMFLOAT3 direction)
{
	//Initialize();


}


Projectile::~Projectile()
{

}

void Projectile::Initialize(DirectX::XMFLOAT3 origin, DirectX::XMFLOAT3 direction)
{
	//position = { 0,0,0 };
	//direction = { 0,0,0 };

	this->position = origin;
	this->direction = direction;

	age = 0.0f;
	speed = 0.5f;
	dmgMultiplier = 2.0f;


	isFired = true;
	collided = false;
	
}

void Projectile::Update(double deltatime)
{

	if(isFired == true)
	{
		age += deltatime;
	}


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

bool Projectile::GetFired()
{
	return isFired;
}

void Projectile::SetFired(bool isFired)
{
	this->isFired = isFired;
}

void Projectile::SetAge(float age)
{
	this->age = age;
}

void Projectile::SetPos(DirectX::XMFLOAT3 pos)
{
	this->position = pos;
}

