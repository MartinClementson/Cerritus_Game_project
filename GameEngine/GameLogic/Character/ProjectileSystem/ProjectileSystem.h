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

	std::vector<Projectile>* projectiles;
	float lifeSpan; //travel time
	int maxProjectiles; // amout of projectiles
	//Player* pos;

public:
	Projectile FireProjectile(XMFLOAT3 origin, XMFLOAT3 direction);
	void UpdateProjectiles(double deltaTime);

	std::vector<Projectile*> projectiles;
	float lifeSpan;
	int maxProjectiles; 
	
	void Initialize();
	void Release();
};