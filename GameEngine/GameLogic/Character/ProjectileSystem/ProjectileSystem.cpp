#include "ProjectileSystem.h"



ProjectileSystem::ProjectileSystem()
{
}


ProjectileSystem::~ProjectileSystem()
{
}

Projectile ProjectileSystem::FireProjectile(DirectX::XMFLOAT3 origin, DirectX::XMFLOAT3 direction)
{ 

	//origin from players pos towards where he is looking.

	return Projectile();
}

void ProjectileSystem::UpdateParticle(double deltaTime)
{


}

void ProjectileSystem::Initialize()
{
	lifeSpan = 2.5f;
	maxProjectiles = 12;

}

void ProjectileSystem::Release()
{
}
