#pragma once
#include "../../StateClass/StateClass.h"
#include "../../../Character/Enemy/Enemy.h"
class EnemyDeathState :
	public StateClass
{
public:
	EnemyDeathState();
	~EnemyDeathState();
	void Initialize();
	void Release();
	void Update(double deltaTime);
private:
	void AIPattern();
	void OnEnter();
	void OnExit();

};

