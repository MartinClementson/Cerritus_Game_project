#pragma once
#include "StateClass.h"
class AttackState :
	public StateClass
{
public:
	AttackState();
	~AttackState();
	void Initialize();
	void Release();
	void Update(double deltaTime);
	void Render();
private:
	void AIPattern();
	void OnEnter();
	void OnExit();
};

