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
	
}

void Trap::Release()
{

}

void Trap::Update(double deltaTime)
{
	//uppdatera dmg och position för varje update. 

	//animation toggle
	//mesh toggle

	//if (position.x = 0 && position.z == 0)
	//{
	//	position.x = rand() % 100 + 1;
	//	position.y = rand() % 100 + 1;
	//}


	//randomize the placement of the traps ? 
	//damage during dot duration
	//Dont know what to update inside here. 

}

void Trap::Render()
{
	//Tar inte scene hand om render för alla traps? jo
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

void Trap::SetPosition(DirectX::XMFLOAT3 position)
{
	this->position = position;
}
