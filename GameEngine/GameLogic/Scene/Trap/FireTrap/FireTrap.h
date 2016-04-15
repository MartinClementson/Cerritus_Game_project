#pragma once
#include "../Trap.h"
#include "../../../StateMachines/TrapStateMachine/TrapStateMachine.h"
class FireTrap :
	public Trap
{
public:
	FireTrap();
	virtual ~FireTrap();
	void Initialize();
	void Release();
	void Update(double deltaTime);
	void Render();
	//Collision();
private:
	float dotDuration;
	TrapStateMachine* TrapState;
};

