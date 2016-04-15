#pragma once
#include "../../StateClass/StateClass.h"
class TrapIdleState :
	public StateClass
{
public:
	TrapIdleState();
	virtual ~TrapIdleState();
	void Initialize();
	void Release();
	void Render();
	void Update(double deltaTime);
private:
	void OnEnter();
	void OnExit();
};

