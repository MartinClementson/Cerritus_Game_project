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
		slow -= (float)deltaTime; 	
	}
	renderInfo.position = position;
	renderInfo.rotation = rotation; 
}

void BearTrap::Render()
{
	if (this->isActive)
	{
		grapichs->QueueRender(&this->renderInfo);
	}
}

float BearTrap::GetSlow()
{
	return slow;
}

void BearTrap::SetSlow(float slow)
{
	this->slow = slow;
}




