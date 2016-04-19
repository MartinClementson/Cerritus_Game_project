#pragma once
#include "../Character.h"
#include "../../StateMachines/EnemyStateMachine/EnemyStateMachine.h"
#include "../../../Source//LibIncluder.h"
#include "../../../Enumerations/Enumerations.h"
#include "../../InputHandler/Input/Input.h"
#include "../../../../GameEngine/Structs/RenderInfo.h"

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
	
	

protected:
	
	
	//float movementSpeed, health, damage;

private:
	EnemyStateMachine* enemyState;
	RenderInfoEnemy renderInfo;
};

