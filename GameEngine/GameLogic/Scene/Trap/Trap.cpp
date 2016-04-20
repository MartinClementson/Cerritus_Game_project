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
	position = { 0,0,0 };
	rotation = { 0,0,0 };
}
void Trap::Release()
{

}
void Trap::Update(double deltaTime)
{

	renderInfo = { position,rotation };


}

void Trap::Render()
{

	//Tar inte scene hand om render för alla traps? jo
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
	return position;
}
DirectX::XMFLOAT3 Trap::GetRotation()
{
	return rotation;
}

void Trap::SetPosition(DirectX::XMFLOAT3 position)
{
	this->position = position;
}

void Trap::SetRotation(DirectX::XMFLOAT3 rotation)
{
	this->rotation = rotation;


}
