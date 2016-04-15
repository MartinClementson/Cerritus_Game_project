#pragma once
#include "StateClass.h"
class EnemyDeathState :
	public StateClass
{
public:
	EnemyDeathState();
	~EnemyDeathState();
	void Initialize();
	void Release();
	void Update(double deltaTime);
	void Render();
private:
	void AIPattern();
	void OnEnter();
	void OnExit();
};

