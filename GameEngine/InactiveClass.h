#pragma once
#include "StateClass.h"
class InactiveClass :
	public StateClass
{
public:
	InactiveClass();
	virtual ~InactiveClass();
	void Initialize();
	void Release();
	void Render();
	void Update(double deltaTime);
private:
	void OnEnter();
	void OnExit();
};

