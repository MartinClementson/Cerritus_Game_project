#pragma once
#include "LibIncluder.h"
#include "Projectile.h"

class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();
	
private:
	std::vector<Projectile> projectiles;
	float lifeSpan;
	int maxProjectiles;

public:
	Projectile FireProjectile(DirectX::XMFLOAT3 origin, DirectX::XMFLOAT3 direction);
	void UpdateParticle();
	void Initialize();
	void Release();
};

