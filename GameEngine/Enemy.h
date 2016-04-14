#pragma once
#include "Character.h"
#include "EnemyStateMachine.h"
class Enemy :
	public Character
{
public:
	Enemy();
	~Enemy();
	void Initialize();
	void Release();
	void Update(double deltaTime);
	void Render();
private:
	EnemyStateMachine* enemyState;
};

