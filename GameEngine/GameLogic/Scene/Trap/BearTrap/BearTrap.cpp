#include "BearTrap.h"



BearTrap::BearTrap()
{
}


BearTrap::~BearTrap()
{
}

void BearTrap::Initialize()
{
	slow = 2.5f; // 2.5 seconds slow
}

void BearTrap::Release()
{

}

void BearTrap::Update(double deltaTime)
{
	if (slow >= 2.5)
	{
		//something i guess
	}
}

void BearTrap::Render()
{

}

float BearTrap::GetSlow()
{
	return slow;
}

void BearTrap::SetSlow(float slow)
{
	this->slow = slow;
}
