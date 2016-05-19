#pragma once
#include "../Character.h"
#include "../../../Source/LibIncluder.h"
#include "../../InputHandler/Input/Input.h"
#include "../ProjectileSystem/ProjectileSystem.h"
#include "../../../Enumerations/Enumerations.h"
#include "../../../Structs/RenderInfo.h"
#include "../../StateMachines/AudioManager/AudioManager.h"

struct Vec3
{
	float x;
	float y;
	float z;

	Vec3() { x = 0; y = 0; z = 0; };
	Vec3(float x, float y, float z) { this->x = x; this->y = y; this->z = z; };

	Vec3 operator+(Vec3 v)
	{
		return Vec3(this->x + v.x, this->y + v.y, this->z + v.z);
	}


	Vec3 operator*(const float& f)
	{
		return Vec3(this->x * f, this->y * f, this->z * f);
	}

	inline float LengthSqrd()
	{
		if (x + y + z != 0)
			return (x*x + y*y + z*z);
		else
			return NULL;
	}
	float Length()
	{
		float l = LengthSqrd();
		if(l != NULL)
			return sqrt(l);
		else 
			return NULL;
	}

	Vec3 Normalize()
	{
		float l = Length();
		
		
		return Vec3 (x /= l,		y /= l,		z /= l);
	}



};


#define Y_OFFSET 0.0f //Because the mesh shall hover
#define VELOCITY_MAX 500.0f
class Player :
	public Character
{
public:
	Player();
	virtual ~Player ();

	void Initialize (AudioManager* audioManager);
	void Release	();
	void Update		(double deltaTime,XMFLOAT3 direction, bool collision);
	void Render		();
	void Move		(MovementDirection* dir,int keyAmount, double deltaTime);
	void Shoot		(InputKeys input, double deltaTime);

	XMFLOAT3 GetPosition()  { return this->position; };
	float GetRadius()		{ return this->radius;   };
	float GetRadius2()		{ return this->radius2;  };
	XMFLOAT3 GetDirection() { return this->direction; };
	Vec3 GetVelocity() { return this->velocity; };
	Vec3 GetAcceleration() { return this->acceleration; };
	float GetFalloffFactor() { return this->fallOfFactor; };
	void  SetHealth(float health);
	void  SetPoints(float points);
	void  SetMulti(float multi);
	float GetHealth();
	float GetPoints();
	float GetMulti();
	
	float hover = 0.0f;
	float GetMaxHealth();
	
	

	UpgradeType		  GetUpgrade();
	void SetUpgrade(UpgradeType upgrade);

	void UpgradeWeapon();
	void DowngradeWeapon();

public:
	UpgradeType upgrade;
	Input*			  userInput;
	ProjectileSystem* projectileSystem;
	float VelocityMax; 
	float slowTimer;
	Vec3 acceleration		= Vec3(0.0f, 0.0f, 0.0f);

private:
	MeshEnum meshID;//enum
	RenderInfoChar renderInfo;

	AntTweakBar *bar = AntTweakBar::GetInstance();
	XMFLOAT3 direction;
	//Collision();

	
	Vec3 velocity			= Vec3(0.1f,0.1f,0.1f);
	float fallOfFactor		= 8.0f; //the bigger number, the faster fallOff , this is like friction
	float maxAcceleration	= 6.0f;
	float points;
	float multiplier;


	

};


