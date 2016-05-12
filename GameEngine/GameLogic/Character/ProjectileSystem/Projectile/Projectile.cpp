#include "Projectile.h"
inline DirectX::XMFLOAT3 operator*(DirectX::XMFLOAT3 a, float b) {
	DirectX::XMFLOAT3 result;

	result.x = a.x * b;
	result.y = a.y * b;
	result.z = a.z * b;

	return result;
}

inline DirectX::XMFLOAT3 operator+(DirectX::XMFLOAT3 a, DirectX::XMFLOAT3 b) {
	DirectX::XMFLOAT3 result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;

	return result;
}



Projectile::Projectile()
{

	isFired = false;




}

//void Projectile::Initialize(DirectX::XMFLOAT3 origin, DirectX::XMFLOAT3 direction)
//{
//
//}

Projectile::Projectile(DirectX::XMFLOAT3 origin, DirectX::XMFLOAT3 direction, DirectX::XMFLOAT3 rotation)
{
	Initialize(origin, direction, rotation);


}


Projectile::~Projectile()
{

}

void Projectile::Initialize(DirectX::XMFLOAT3 origin, DirectX::XMFLOAT3 direction, DirectX::XMFLOAT3 rotation)
{


	this->position = origin;
	this->position.y = 3.0f;
	this->direction = direction;
	this->rotation = rotation;
	this->renderInfo.object = MeshEnum::PROJECTILE_1;

	this->radius = 1.0f;
	this->age = 0.0f;
	this->speed = 150.0f;
	this->dmgMultiplier = 2.0f;

	this->isFired = true;
	this->collided = false;

}

void Projectile::Update(double deltatime)
{

	if (isFired == true)
	{

		age += (float)deltatime;

		position = position + (direction* speed * float(deltatime));


		renderInfo.position  = position;
		renderInfo.rotation  = this->rotation;
		renderInfo.direction = this->direction;
		renderInfo.radius    = this->radius;  //Used for frustum culling
		renderInfo.render    = true;			//Used for frustum culling
		//renderInfo.rotation.x += 90;
		//renderInfo.rotation.y += 180;
		
	}
	/*if (age >= 2.5f)
		isFired = false;*/


}

void Projectile::Release()
{

}

void Projectile::Collision()
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
	return this->position;
}

DirectX::XMFLOAT3 Projectile::GetDir()
{
	return this->direction;
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

float Projectile::GetRadius()
{
	return this->radius;
}