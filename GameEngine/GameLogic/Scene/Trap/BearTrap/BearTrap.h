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
	void SetPosition(XMFLOAT3 position);
	void SetRotation(XMFLOAT3 rotation);
	RenderInfoTrap renderinfo;
	DirectX::XMFLOAT3 GetRotation();
	DirectX::XMFLOAT3 GetPosition();

	//Collision();
private:
	float slow;
	TrapStateMachine* TrapState;
	//RenderInfoTrap* renderinfo; 
	Graphics*  grapichs;

};

