#include "FireTrap.h"



FireTrap::FireTrap()
{
	grapichs = Graphics::GetInstance();
}


FireTrap::~FireTrap()
{
}

void FireTrap::Initialize(XMFLOAT3 position,XMFLOAT3 rotation)
{
	dotDuration = 2.5f;  

	this->position = position;
	
	this->rotation = { 0,0,0 }; 
	
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
	renderInfo = { position,rotation };
}

void FireTrap::Render()
{
	grapichs->QueueRender(&renderInfo);
}

float FireTrap::GetDot()
{
	return dotDuration;
}

void FireTrap::SetDot(float dotDuration)
{
	this->dotDuration = dotDuration;
}
