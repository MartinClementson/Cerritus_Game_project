#pragma once
#include "../../../../Source/LibIncluder.h"
#include "../../../../Enumerations/Enumerations.h"

using namespace DirectX;

class Projectile
{
private:
	XMFLOAT3 position;
	XMFLOAT3 direction;

	float age, speed, dmgMultiplier;
	bool isFired, collided;


public:
	void Initialize();
	void Release();
	void Collision();

	MeshEnum projectileModel;
	Projectile();

	void Update(double deltatime);
	float GetAge();
	float GetSpeed();

	XMFLOAT3 GetPos();
	XMFLOAT3 GetDir();


	Projectile(XMFLOAT3 origin, XMFLOAT3 direction);
	virtual ~Projectile();

	void SetAge(float age);
	void SetPos(XMFLOAT3 pos);

};

