#pragma once
#include "StateClass.h"
class DeathState :
	public StateClass
{
public:
	DeathState();
	~DeathState();
	void Initialize();
	void Release();
	void Update(double deltaTime);
	void Render();
private:
	void AIPattern();
};

