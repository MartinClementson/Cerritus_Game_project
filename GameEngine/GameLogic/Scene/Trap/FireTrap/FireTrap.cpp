#include "FireTrap.h"



FireTrap::FireTrap()
{
}


FireTrap::~FireTrap()
{
}

void FireTrap::Initialize()
{
	dotDuration = 2.5f;  
	
}

void FireTrap::Release()
{

}

void FireTrap::Update(double deltaTime)
{ 
	if (dotDuration > 0)
	{
		dotDuration = dotDuration - 1 * (float)deltaTime;
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
