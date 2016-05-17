#include "FireTrap.h"



FireTrap::FireTrap()
{
	graphics = Graphics::GetInstance();
	trapState = new TrapStateMachine();
}

FireTrap::FireTrap(XMFLOAT3 position)
{
	graphics = Graphics::GetInstance();
	
	dotDuration = 5.0f;
	trapState = new TrapStateMachine();

	this->position = position;
	trapState->Initialize();
	this->rotation = { 0,0,0 };
	this->damage = 0.5f;
	Initialize(this->position, this->rotation);

	this->isActive = true;
	this->renderInfo.object = MeshEnum::TRAP_FIRE;
	radius = 5.0f;
}


FireTrap::~FireTrap()
{
	delete trapState;
}

void FireTrap::Initialize(XMFLOAT3 position,XMFLOAT3 rotation)
{
	dotDuration = 5.0f;  

	this->position = position;
	
	this->rotation = { 0,0,0 }; 

	this->isActive = true;
	this->renderInfo.object = MeshEnum::TRAP_FIRE;
	this->renderInfo.radius = radius;
	radius = 10.0f;
	this->activeTimer = 0.0f;

}

void FireTrap::Release()
{

}

void FireTrap::Update(double deltaTime)
{ 

	renderInfo.normalizedReloadVal = -1;
	if (this->currReloadTime > 0)
		currReloadTime -= (float)(deltaTime / 4);
	if (this->GetState()->GetTrapState() == TrapState::TRAP_ACTIVE_STATE)
	{
		this->activeTimer += (float)deltaTime;
	}

	if (activeTimer > 1.0f)
	{
		this->GetState()->SetTrapState(TrapState::TRAP_INACTIVE_STATE);
		activeTimer = 0.0f;
	}

	if (dotDuration > 0)
	{
		dotDuration = dotDuration - 1 * (float)deltaTime;// thinkng of how this will work, need a boolean for if activated and if enemys have collided with it.
	}

	renderInfo.position = position ;
	renderInfo.rotation = rotation;
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

void FireTrap::Render()
{
	if (this->isActive)
	{
		if (this->isBeingReloaded)
			renderInfo.normalizedReloadVal = this->currReloadTime / this->maxReloadTime;
		graphics->QueueRender(&renderInfo);
	}
}

float FireTrap::GetDot()
{
	return damage;
}

void FireTrap::SetDotDur(float dotDuration)
{
	this->dotDuration = dotDuration;
}

TrapStateMachine* FireTrap::GetState()
{
	return trapState;
}
