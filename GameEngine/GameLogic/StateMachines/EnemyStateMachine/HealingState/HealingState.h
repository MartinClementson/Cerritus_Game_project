#pragma once
#include "../../StateClass/StateClass.h"

class HealingState :
	public StateClass
{
public:
	HealingState();
	virtual ~HealingState();
	void Initialize();
	void Release();
	void Update(double deltaTime);
	void AIPattern();
	void OnEnter();
	void OnExit();
};

