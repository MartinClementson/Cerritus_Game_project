#pragma once
#include "../../../../Source/LibIncluder.h"
#include "../../../../Enumerations/Enumerations.h"


class Projectile
{
public:
	
	Projectile(DirectX::XMFLOAT3 origin, DirectX::XMFLOAT3 direction);
	virtual ~Projectile();
private:
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 direction;
	float age, speed, dmgMultiplier;
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


	//Collission();
};

