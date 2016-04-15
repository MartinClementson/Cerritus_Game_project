#pragma once
#include "./ActiveState/ActiveState.h"
#include "./IldeState/TrapIdleState.h"
#include "./InactiveState/InactiveState.h"
#include "../../../Enumerations/Enumerations.h"
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

