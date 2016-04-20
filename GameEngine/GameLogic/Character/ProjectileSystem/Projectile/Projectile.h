#pragma once
#include "../../../../Source/LibIncluder.h"
#include "../../../../Enumerations/Enumerations.h"

using namespace DirectX;

class Projectile
{
private:

	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 direction;

	float age, speed, dmgMultiplier;
	bool isFired, collided;
	MeshEnum projectileModel;
public:
	Projectile();
	void Initialize(DirectX::XMFLOAT3 origin, DirectX::XMFLOAT3 direction);
	void Update(double deltatime);

//	XMFLOAT3 position;
//	XMFLOAT3 direction;

//	float age, speed, dmgMultiplier;
	//bool isFired, collided;


public:

	void Release();
	void Collision();

//	MeshEnum projectileModel;
//	Projectile();

	//void Update(double deltatime);
	float GetAge();
	float GetSpeed();

	bool GetFired();
	void SetFired(bool isFired);

	void SetAge(float age);
	void SetPos(DirectX::XMFLOAT3 pos);
	
	XMFLOAT3 GetPos();
	XMFLOAT3 GetDir();


	Projectile(XMFLOAT3 origin, XMFLOAT3 direction);
	virtual ~Projectile();

	//void SetAge(float age);
	//void SetPos(XMFLOAT3 pos);

};

