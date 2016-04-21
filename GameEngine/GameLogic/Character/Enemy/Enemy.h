#pragma once
#include "../Character.h"
#include "../../../Source//LibIncluder.h"
#include "../../../Enumerations/Enumerations.h"
#include "../../InputHandler/Input/Input.h"
#include "../../../../GameEngine/Structs/RenderInfo.h"
#include "../../StateMachines/EnemyStateMachine/EnemyStateMachine.h"
#include "../../../Structs/DataTypes.h"
#include "../Player/Player.h"

class Enemy :
	public Character
{
protected:

	float movementSpeed, health, damage;
private:
	RenderInfoEnemy renderInfo;
	EnemyStateMachine* enemyStateMachine;
	Player * player;
private:
	void Release();
	Enemy();
public:
	Enemy(XMFLOAT3 spawn);

	bool isAlive;

	virtual ~Enemy();

	void Initialize();

	void Update(double deltaTime);

	void Render();
	XMFLOAT3 GetPosition();
	float GetRadius();
	void AIPattern(Player * player, double deltaTime);
	void Respawn(XMFLOAT3 spawn);
};

