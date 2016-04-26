#include "BearTrap.h"



BearTrap::BearTrap(XMFLOAT3 position)
{
	grapichs = Graphics::GetInstance();
	slow = 0.5f;
	this->position = position;
	this->rotation = { 0,0,0 };
	this->isActive = true;
	this->renderInfo.object = MeshEnum::TRAP_BEAR;

	radius = 1.0f;
}

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
	this->isActive = true;
	this->renderInfo.object = MeshEnum::TRAP_BEAR;
	radius = 1.0f;

}

void BearTrap::Release()
{

}

void BearTrap::Update(double deltaTime)
{
	if (slow > 0.0f)
	{
		slow -= (float)deltaTime; // thinkng of how this will work, need a boolean for if activated and if enemys have collided with it.

		//slow = slow - 1 * (float)deltaTime;// la till delta time av samma anledning som i fire

	}

	renderInfo.position = position;
	renderInfo.rotation = rotation; // kinda works

}

void BearTrap::Render()
{
	if (this->isActive)
	{
		grapichs->QueueRender(&this->renderInfo);
	}

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




