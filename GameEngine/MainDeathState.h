#pragma once
#include "StateClass.h"
class MainDeathState :
	public StateClass
{
public:
	MainDeathState();
	~MainDeathState();
	void Initialize();
	void Release();
	void Update(double deltaTime);
	void Render();
private:
	void OnEnter();
	void OnExit();
};

