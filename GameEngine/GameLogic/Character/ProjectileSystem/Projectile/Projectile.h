#pragma once
#include "../../../../Source/LibIncluder.h"
#include "../../../../Enumerations/Enumerations.h"

using namespace DirectX;

class Projectile
{
public:
	Projectile();

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
};

