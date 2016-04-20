#pragma once
#include "../Character.h"
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
	RenderInfoEnemy renderInfo;
private:
	void Release();
public:
	Enemy(XMFLOAT3 spawn);
	Enemy();
	virtual ~Enemy();

	void Initialize(XMFLOAT3 position);

	void UpdateAttack(double deltaTime);
	void UpdateIdle(double deltaTime);
	bool IdleBool(bool idle);
	void UpdateDead(double deltaTime);

	bool DeadBool(bool dead);

	void Render();
};

