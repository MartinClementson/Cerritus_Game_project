#pragma once
#include "../Character.h"
#include "../../StateMachines/EnemyStateMachine/EnemyStateMachine.h"
class Enemy :
	public Character
{
public:
	Enemy();
	virtual ~Enemy();
	void Initialize();
	void Release();
	void Update(double deltaTime);
	void Render();
private:
	EnemyStateMachine* enemyState;
};

