#pragma once
#include "../../../../Source/LibIncluder.h"
#include "../../../../Enumerations/Enumerations.h"

using namespace DirectX;

class Projectile
{
public:
	Projectile();
	
	Projectile(DirectX::XMFLOAT3 origin, DirectX::XMFLOAT3 direction);
	virtual ~Projectile();
private:
	XMFLOAT3 position;
	XMFLOAT3 direction;
	MeshEnum projectileModel;

	float age, speed, dmgMultiplier;

	bool isFired, colided;

private:

public:
	void Initialize();
	void Release();
	void Collision();

	bool isFired, collided;
	MeshEnum projectileModel;
	Projectile();
public:
	void Initialize();
	void Release();
	float GetAge();
	float GetSpeed();
	DirectX::XMFLOAT3 GetPos();
	DirectX::XMFLOAT3 GetDir();

	void SetAge(float age);
	void SetPos(DirectX::XMFLOAT3 pos);

};

