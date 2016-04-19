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
		dotDuration = dotDuration - 1;
	}

}

void FireTrap::Render()
{

}

float FireTrap::GetDot()
{
	return dotDuration;
}

void FireTrap::SetDot(float dotDuration)
{
	this->dotDuration = dotDuration;
}
