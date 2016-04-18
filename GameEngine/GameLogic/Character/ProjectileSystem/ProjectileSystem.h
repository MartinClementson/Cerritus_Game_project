#pragma once
#include "../../../Source/LibIncluder.h"
#include "../ProjectileSystem/Projectile/Projectile.h"
#include "../Player/Player.h"
class ProjectileSystem
{
public:
	ProjectileSystem();
	virtual ~ProjectileSystem();
	
private:
	std::vector<Projectile> projectiles;
	float lifeSpan; //travel time
	int maxProjectiles; // amout of projectiles
	//Player* pos;

public:
	Projectile FireProjectile(DirectX::XMFLOAT3 origin, DirectX::XMFLOAT3 direction);
	void UpdateParticle(double deltaTime);
//	void UpdateProjectile(double deltaTime);
	void Initialize();
	void Release();
};