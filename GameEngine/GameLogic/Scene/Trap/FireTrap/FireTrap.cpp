#include "FireTrap.h"



FireTrap::FireTrap()
{
	grapichs = Graphics::GetInstance();
}

FireTrap::FireTrap(XMFLOAT3 position)
{
	grapichs = Graphics::GetInstance();
	dotDuration = 2.5f;
	
	this->position = position;

	this->rotation = { 0,0,0 };
	this->damage = 10;

	this->isActive = true;
	this->renderInfo.object = MeshEnum::TRAP_FIRE;
	radius = 1.0f;
}


FireTrap::~FireTrap()
{
}

void FireTrap::Initialize(XMFLOAT3 position,XMFLOAT3 rotation)
{
	dotDuration = 2.5f;  

	this->position = position;
	
	this->rotation = { 0,0,0 }; 

	this->isActive = true;
	this->renderInfo.object = MeshEnum::TRAP_FIRE;

	radius = 1.0f;

}

void FireTrap::Release()
{

}

void FireTrap::Update(double deltaTime)
{ 
	if (dotDuration > 0)
	{
		dotDuration = dotDuration - 1 * deltaTime;// thinkng of how this will work, need a boolean for if activated and if enemys have collided with it.

		//dotDuration = dotDuration - 1 * (float)deltaTime;

	}
	renderInfo.position = position ;
	renderInfo.rotation = rotation;
}	

void FireTrap::Render()
{
	if (this->isActive)
	{
		grapichs->QueueRender(&renderInfo);
	}
}

float FireTrap::GetDot()
{
	return damage;
}

void FireTrap::SetDotDur(float dotDuration)
{
	this->dotDuration = dotDuration;
}
