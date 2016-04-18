#pragma once
#include "../../../StateClass/StateClass.h"
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
	void ProcessInput();
private:
	void OnEnter();
	void OnExit();
};

