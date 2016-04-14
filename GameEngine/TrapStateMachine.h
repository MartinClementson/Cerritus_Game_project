#pragma once
#include "ActiveState.h"
#include "TrapIdleState.h"
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
	InactiveState* InactiveState;
	TrapIdleState* idleState;
	//TrapState activeState;//enum
};

