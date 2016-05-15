#include "BearTrap.h"



BearTrap::BearTrap(XMFLOAT3 position)
{
	grapichs = Graphics::GetInstance();
	slow = 0.5f;
	this->position = position;
	this->rotation = { 0,0,0 };
	this->isActive = true;
	this->renderInfo.object = MeshEnum::TRAP_BEAR;
	trapState = new TrapStateMachine();
	trapState->Initialize();
	
	radius = 1.0f;
	radius2 = 10.0f;
}

BearTrap::BearTrap()
{
	grapichs = Graphics::GetInstance();
	
}


BearTrap::~BearTrap()
{
	delete trapState;
}

void BearTrap::Initialize(XMFLOAT3 position, XMFLOAT3 rotation)
{
	slow = 0.5f; 
	this->position = position;
	this->rotation = { 0,0,0 };
	this->isActive = true;
	this->renderInfo.object = MeshEnum::TRAP_BEAR;
	this->renderInfo.radius = radius;
	radius = 2.0f;
	radius2 = 3.0f;
	activeTimer = 0.0f;

}

void BearTrap::Release()
{

}

void BearTrap::Update(double deltaTime)
{
	//this->isBeingReloaded = false; //Needs to be reset every frame, in case the player releases the button
	renderInfo.normalizedReloadVal = -1;
	if (this->currReloadTime > 0)
		currReloadTime -=  (float)(deltaTime/4);
	
	if (this->GetState()->GetTrapState() == TrapState::TRAP_ACTIVE_STATE)
	{
		activeTimer += (float)deltaTime;
	}

	if (activeTimer > 1.0f)
	{
		this->GetState()->SetTrapState(TrapState::TRAP_INACTIVE_STATE);
		activeTimer = 0.0f;
	}

	if (slow > 0.0f)
	{
		slow -= (float)deltaTime; 	
	}

	renderInfo.position = position;
	renderInfo.rotation = rotation; // kinda works
	renderInfo.radius = radius;
	renderInfo.render = true;

	if (this->GetState()->GetTrapState() != TrapState::TRAP_INACTIVE_STATE)
	{
		renderInfo.glow = true;
	}
	else
	{
		renderInfo.glow = false;
	}

}

void BearTrap::Render()
{
	if (this->isActive)
	{
		
			if (this->isBeingReloaded)
				renderInfo.normalizedReloadVal = this->currReloadTime / this->maxReloadTime;
			
				
		
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

TrapStateMachine* BearTrap::GetState()
{
	return trapState;
}




