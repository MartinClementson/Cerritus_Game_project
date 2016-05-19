#pragma once
#include "../Character.h"
#include "../../../Source/LibIncluder.h"
#include "../../../Enumerations/Enumerations.h"
#include "../../InputHandler/Input/Input.h"
#include "../../../../GameEngine/Structs/RenderInfo.h"
#include "../../StateMachines/EnemyStateMachine/EnemyStateMachine.h"
#include "../../../Structs/DataTypes.h"
#include "../Player/Player.h"
#include "../../Scene/Trap/BearTrap/BearTrap.h"



class EnemyBase :
	public Character
{
protected:
	Vec3 direction; //walking direction
	RenderInfoEnemy renderInfo;
	EnemyStateMachine* enemyStateMachine;
	Player * player;
	bool fast;
	CharacterType charType;
	float maxHealth;
	EnemyBase* closestHealer;
	float animationTime;
	float animationSpeed = 0.003f;
	EnemyAnimations animation;
	
	EnemyBase();
public:
	bool healable = NULL;
	bool isBeingHealed = false;
	virtual void Release();
	int healing;
	virtual CharacterType GetCharType();
	
	float index;

	virtual EnemyStateMachine* GetStateMachine();
	virtual void AIPatternHeal(EnemyBase * player, double deltaTime);

	bool isAlive;

	virtual ~EnemyBase();

	virtual void Initialize();

	virtual void Update(double deltaTime);

	virtual float GetHealth();

	virtual float GetMaxHealth();
	virtual void SetClosestHealer(EnemyBase* healer);
	virtual EnemyBase* GetClosestHealer();

	virtual void SetHealth(float health);

	virtual void Render();
	virtual XMFLOAT3 GetPosition();
	virtual void SetPosition(XMFLOAT3 pos);
	virtual float GetRadius();
	virtual float GetRadius2();
	virtual void AIPattern(Player * player, double deltaTime);
	virtual void EnemyWithEnemyCollision(EnemyBase* enemy, EnemyBase* enemys, double deltaTime);

	//void EnemyWithBeartrap(BearTrap * bear, Enemy * enemys, double deltaTime);
	virtual void Respawn(XMFLOAT3 spawn);
	virtual void Spawn(XMFLOAT3 spawn);

	float originalMovementSpeed = 0;
	float slowTimer;
	void SetAnimation(EnemyAnimations animation)
	{ 
		if( this->animation != animation)
		{
			this->animation = animation; 
			animationTime = 0.0f; 
		}
	
	};

};
