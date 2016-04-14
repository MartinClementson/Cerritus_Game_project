#pragma once
#include "ActiveState.h"
#include "IdleState.h"
#include "InactiveState.h"
class TrapStateMachine
{
public:
	TrapStateMachine();
	virtual ~TrapStateMachine();

	void Initialize();
	void Release();
	void Update(double deltaTime);
	void Render();
private:
	ActiveState* activeState;
	InactiveState* activeState;
	IdleState* idleState;
	//TrapState activeState;//enum
};

