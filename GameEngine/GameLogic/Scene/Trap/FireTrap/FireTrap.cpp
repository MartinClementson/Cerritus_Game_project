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
		dotDuration = dotDuration - 1 * deltaTime; // la till deltaTime annars försvinner doten innan den gör något
	}
}

void FireTrap::Render()
{
	//hur ska render fungera i fire och bear trap? 
}

float FireTrap::GetDot()
{
	return dotDuration;
}

void FireTrap::SetDot(float dotDuration)
{
	this->dotDuration = dotDuration;
}
