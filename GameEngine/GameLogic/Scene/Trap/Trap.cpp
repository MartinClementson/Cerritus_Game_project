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
	position = { 1,0,2 };
	rotation = { 0,0,0 };

}
void Trap::Release()
{

}
void Trap::Update(double deltaTime)
{

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
