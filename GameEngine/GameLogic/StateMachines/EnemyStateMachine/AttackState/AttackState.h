#pragma once
#include "../../StateClass/StateClass.h"

class AttackState :
	public StateClass
{
private:
	void AIPattern();
	void OnEnter();
	void OnExit();

public:
	AttackState();
	~AttackState();

	void Initialize();
	void Release();
	void Update(double deltaTime);
};

