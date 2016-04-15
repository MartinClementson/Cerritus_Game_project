#pragma once
#include "../../../StateClass/StateClass.h"
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
	void ProcessInput();
private:
	void OnEnter();
	void OnExit();
};

