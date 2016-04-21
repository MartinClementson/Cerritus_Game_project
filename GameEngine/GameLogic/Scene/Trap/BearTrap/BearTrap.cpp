#include "BearTrap.h"



BearTrap::BearTrap()
{
	grapichs = Graphics::GetInstance();

}


BearTrap::~BearTrap()
{
}

void BearTrap::Initialize(XMFLOAT3 position, XMFLOAT3 rotation)
{
	slow = 0.5f; 
	this->position = position;
	this->rotation = { 0,0,0 };
}

void BearTrap::Release()
{

}

void BearTrap::Update(double deltaTime)
{
	if (slow > 0.0f)
	{
		slow -=deltaTime; // thinkng of how this will work, need a boolean for if activated and if enemys have collided with it.
	}

	renderinfo = {position,rotation}; // kinda works

}

void BearTrap::Render()
{
	grapichs->QueueRender(&renderinfo);
	//grapichs->QueueRender(renderinfo); Unsure if the other one works. will see
}

float BearTrap::GetSlow()
{
	return slow;
}

void BearTrap::SetSlow(float slow)
{
	this->slow = slow;
}

void BearTrap::SetPosition(XMFLOAT3 position)
{
	this->position = position;
}
void BearTrap::SetRotation(XMFLOAT3 rotation)
{
	this->rotation = rotation;
}

DirectX::XMFLOAT3 BearTrap::GetRotation()
{
	return this->rotation;
}

DirectX::XMFLOAT3 BearTrap::GetPosition()
{
	return this->position;
}


