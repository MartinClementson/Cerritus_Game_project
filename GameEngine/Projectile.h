#pragma once
#include "LibIncluder.h"
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
public:
	void Initialize();
	void Release();
	//Collission();
};

