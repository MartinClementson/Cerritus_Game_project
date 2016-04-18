#pragma once
#include "../../../Source/LibIncluder.h"
#include "../ProjectileSystem/Projectile/Projectile.h"
//#include "../Player/Player.h"
//#include "../../Character/Character.h"
class ProjectileSystem
{
public:
	ProjectileSystem();
	virtual ~ProjectileSystem();
	
private:
	std::vector<Projectile*> projectiles;
	float lifeSpan;
	int maxProjectiles; 
	

public:
	void FireProjectile(DirectX::XMFLOAT3 origin, DirectX::XMFLOAT3 direction);
	void UpdateParticle(double deltaTime);
	void Initialize();
	void Release();
};