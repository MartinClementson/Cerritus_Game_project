#pragma once
#include "../../../Source/LibIncluder.h"
#include "../ProjectileSystem/Projectile/Projectile.h"

class ProjectileSystem
{
public:
	ProjectileSystem();
	virtual ~ProjectileSystem();
	
private:
	std::vector<Projectile> projectiles;
	float lifeSpan;
	int maxProjectiles;

public:
	Projectile FireProjectile(DirectX::XMFLOAT3 origin, DirectX::XMFLOAT3 direction);
	void UpdateParticle(double deltaTime);
	void Initialize();
	void Release();
};