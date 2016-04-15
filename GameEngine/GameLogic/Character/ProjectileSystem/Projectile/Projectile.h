#pragma once
#include "LibIncluder.h"
#include "Enumerations.h"
class Projectile
{
public:
	Projectile();
	virtual ~Projectile();
private:
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 direction;
	float age, speed, dmgMultiplier;
	bool isFired, colided;
	Meshes projectileModel;
public:
	void Initialize();
	void Release();
	//Collission();
};

