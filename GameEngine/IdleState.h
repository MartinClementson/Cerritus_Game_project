#pragma once
#include "StateClass.h"
class IdleState :
	public StateClass
{
public:
	IdleState();
	~IdleState();
	void Initialize();
	void Release();
	void Update(double deltaTime);
	void Render();
private:
	void AIPattern();
};

