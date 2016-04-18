#pragma once
#include "../../StateClass/StateClass.h"
class InactiveState :
	public StateClass
{
public:
	InactiveState();
	virtual ~InactiveState();
	void Initialize();
	void Release();
	void Render();
	void Update(double deltaTime);
private:
	void OnEnter();
	void OnExit();
};

