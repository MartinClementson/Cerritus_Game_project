#pragma once
#include "../../StateClass/StateClass.h"
class ActiveState :
	public StateClass
{
public:
	ActiveState();
	virtual ~ActiveState();
	void Initialize();
	void Release();
	void Render();
	void Update(double deltaTime);
private:
	void OnEnter();
	void OnExit();
};

