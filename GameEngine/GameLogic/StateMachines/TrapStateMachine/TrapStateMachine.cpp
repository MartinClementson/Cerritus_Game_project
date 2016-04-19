#include "TrapStateMachine.h"



TrapStateMachine::TrapStateMachine()
{
	this->activeState = new ActiveState();
	this->idleState = new TrapIdleState();
	this->inactiveState = new InactiveState();
}


TrapStateMachine::~TrapStateMachine()
{
	delete this->activeState;
	delete this->idleState;
	delete this->inactiveState;
}

void TrapStateMachine::Initialize()
{
	activeState->Initialize();
}

void TrapStateMachine::Release()
{
}

void TrapStateMachine::Update(double deltaTime)
{
	if (activeState->isActive)
	{
		activeState->Update(deltaTime);
	}
	else if (inactiveState->isActive)
	{
		inactiveState->Update(deltaTime);
	}
	else if (idleState->isActive)
	{
		idleState->Update(deltaTime);
	}
}

void TrapStateMachine::Render()
{
	if (activeState->isActive)
	{
		activeState->Render();
	}
	else if (inactiveState->isActive)
	{
		inactiveState->Render();
	}
	else if (idleState->isActive)
	{
		idleState->Render();
	}
}
