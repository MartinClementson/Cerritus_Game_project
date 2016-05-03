#pragma once
#include "EnemyBase.h"
#include "../../../Source//LibIncluder.h"
#include "../../../Enumerations/Enumerations.h"
#include "../../InputHandler/Input/Input.h"
#include "../../../../GameEngine/Structs/RenderInfo.h"
#include "../../StateMachines/EnemyStateMachine/EnemyStateMachine.h"
#include "../../../Structs/DataTypes.h"
#include "../Player/Player.h"
#include "../../Scene/Trap/BearTrap/BearTrap.h"
#include "Healer.h"



class Enemy :
	public EnemyBase
{
private:
	//RenderInfoEnemy renderInfo;
	//EnemyStateMachine* enemyStateMachine;
	//Player * player;
	//bool fast;
public:
	void Release();
	Enemy();
	float index;

	EnemyStateMachine* GetStateMachine();
	
	Enemy(XMFLOAT3 spawn, bool fast);

	//bool isAlive = false;

	~Enemy();

	
	void Initialize();



	void Update(double deltaTime);

	float GetHealth();

	void SetHealth(float health);

	void Render();
	XMFLOAT3 GetPosition();
	void SetPosition(XMFLOAT3 pos);
	float GetRadius();
	float GetRadius2();
	void AIPattern(Player * player, double deltaTime);
	void AIPatternHeal(EnemyBase * player, double deltaTime);
	CharacterType GetCharType();
	void EnemyWithEnemyCollision(Enemy * enemy, Enemy * enemys, double deltaTime);
	
	//void EnemyWithBeartrap(BearTrap * bear, Enemy * enemys, double deltaTime);
	void Respawn(XMFLOAT3 spawn);
	void Spawn(XMFLOAT3 spawn);
};