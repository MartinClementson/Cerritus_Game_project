#pragma once
#include "../Trap.h"
#include "../../../StateMachines/TrapStateMachine/TrapStateMachine.h"
class FireTrap :
	public Trap
{
public:
	FireTrap(XMFLOAT3 position);
	virtual ~FireTrap();
	void Initialize(XMFLOAT3 position, XMFLOAT3 rotation);
	void Release();
	void Update(double deltaTime);
	void Render();
	float GetDot();
	void SetDotDur(float dotDuration);
	RenderInfoTrap renderInfo;
	TrapStateMachine* GetState();

	//Collision();
private:
	FireTrap();
	float dotDuration;
	TrapStateMachine* trapState;
	//RenderInfoTrap renderInfo;
	//RenderInfoTrap* renderInfo;
	Graphics* grapichs;
	float activeTimer;
};

