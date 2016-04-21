#include "FireTrap.h"



FireTrap::FireTrap()
{
	grapichs = Graphics::GetInstance();
}


FireTrap::~FireTrap()
{
}

void FireTrap::Initialize()
{
	dotDuration = 2.5f;  
	position = { 2.0f,5.0f,2.0f };
	rotation = { 0.0f,0.0f,0.0f };
	
}

void FireTrap::Release()
{

}

void FireTrap::Update(double deltaTime)
{ 
	if (dotDuration > 0)
	{
		dotDuration = dotDuration - 1 * deltaTime;// thinkng of how this will work, need a boolean for if activated and if enemys have collided with it.
	}

	renderInfo = { position,rotation }; //must check this.. 
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
