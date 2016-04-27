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

	activeStateEnum = TrapState::TRAP_IDLE_STATE;
	//activeState->Initialize();
	//idleState->Initialize();
	//inactiveState->Initialize();

}

void TrapStateMachine::Release()
{

}

void TrapStateMachine::Update(double deltaTime)
{
	if (activeStateEnum == TRAP_IDLE_STATE)
	{
		activeState->Update(deltaTime);
	}
	else if (activeStateEnum==TRAP_INACTIVE_STATE)
	{
		inactiveState->Update(deltaTime);
	}
	else if (activeStateEnum == TRAP_ACTIVE_STATE)
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

TrapState TrapStateMachine::GetTrapState()
{
	
	return activeStateEnum;
}

void TrapStateMachine::SetTrapState(TrapState state)
{
	this->activeStateEnum = state;
}
