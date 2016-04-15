#pragma once
#include "ActiveState.h"
#include "TrapIdleState.h"
#include "InactiveState.h"
#include "Enumerations.h"
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
	InactiveState* InactiveState;
	TrapIdleState* idleState;
	TrapState activeStateEnum;//enum
};

