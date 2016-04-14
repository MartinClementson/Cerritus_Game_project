#pragma once
#include "StateClass.h"
class MainPausedState :
	public StateClass
{
public:
	MainPausedState();
	~MainPausedState();
	void Initialize();
	void Release();
	void Update(double deltaTime);
	void Render();
private:
	void OnEnter();
	void OnExit();
};

