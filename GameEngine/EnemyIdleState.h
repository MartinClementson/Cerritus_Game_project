#pragma once
#include "StateClass.h"
class EnemyIdleState :
	public StateClass
{
public:
	EnemyIdleState();
	~EnemyIdleState();
	void Initialize();
	void Release();
	void Update(double deltaTime);
	void Render();
private:
	void AIPattern();
	void OnEnter();
	void OnExit();
};

