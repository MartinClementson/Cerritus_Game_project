#pragma once
#include "../../StateClass/StateClass.h"
#include "../../../Character/Enemy/Enemy.h"

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

