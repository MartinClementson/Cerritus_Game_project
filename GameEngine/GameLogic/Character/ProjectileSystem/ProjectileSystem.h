#pragma once
#include "../../../Source/LibIncluder.h"
#include "../ProjectileSystem/Projectile/Projectile.h"

using namespace DirectX;


class ProjectileSystem
{
public:
	ProjectileSystem();
	virtual ~ProjectileSystem();
	
private:

	std::vector<Projectile*> projectiles;
	float lifeSpan; //travel time
	int maxProjectiles; // amout of projectiles
	//Player* pos;

public:
	void FireProjectile(XMFLOAT3 origin, XMFLOAT3 direction);
	void UpdateProjectiles(double deltaTime);

	void Initialize();
	void Release();
};