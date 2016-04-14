#pragma once
#include "Trap.h"
#include "TrapStateMachine.h"
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
	//Collision();
private:
	float slow;
	TrapStateMachine* TrapState;
};

