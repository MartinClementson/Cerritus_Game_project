#pragma once
#include "../Character.h"
#include "../../StateMachines/EnemyStateMachine/EnemyStateMachine.h"
#include "../../../Source//LibIncluder.h"
#include "../../../Enumerations/Enumerations.h"
#include "../../InputHandler/Input/Input.h"
#include "../../../../GameEngine/Structs/RenderInfo.h"
#include "../Enemy/Enemy.h"

class Enemy :
	public Character
{
protected:
	float movementSpeed, health, damage;

private:
	EnemyStateMachine* enemyState;
	RenderInfoEnemy renderInfo;
private:

public:
	Enemy();
	virtual ~Enemy();

	void Initialize(XMVECTOR position);
	void Release();
	void Update(double deltaTime);
	void Render();
};

