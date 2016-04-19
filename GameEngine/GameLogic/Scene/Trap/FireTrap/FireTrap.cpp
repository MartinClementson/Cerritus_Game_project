#include "FireTrap.h"



FireTrap::FireTrap()
{
}


FireTrap::~FireTrap()
{
}

void FireTrap::Initialize()
{
	dotDuration = 2.5f; // 2.5 sec 
	
}

void FireTrap::Release()
{
}

void FireTrap::Update(double deltaTime)
{
	//dotduration 
	if (dotDuration >= 2.5)
	{
		
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
