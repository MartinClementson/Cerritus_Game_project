#pragma once
#include "../Trap.h"
#include "../../../StateMachines/TrapStateMachine/TrapStateMachine.h"
class BearTrap :
	public Trap
{
public:
	BearTrap();
	virtual ~BearTrap();
	void Initialize();
	void Release();
	void Update(double deltaTime);
	void Render();
	float GetSlow();
	void SetSlow(float slow);

	//Collision();
private:
	float slow;
	TrapStateMachine* TrapState;
};

