#pragma once
#include "../../StateClass/StateClass.h"
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

private:
	void AIPattern();
	void OnEnter();
	void OnExit();
};

