#include "ProjectileSystem.h"



ProjectileSystem::ProjectileSystem()
{

}


ProjectileSystem::~ProjectileSystem()
{

}

Projectile ProjectileSystem::FireProjectile(DirectX::XMFLOAT3 origin, DirectX::XMFLOAT3 direction)
{
	//position where the projectiles are fired from is the position of the player and the aim of the mouse i guess.
	//where are they shoot two 

	return Projectile();
}

void ProjectileSystem::UpdateParticle(double deltaTime)
{
	//update misses and hits, and position.



}

void ProjectileSystem::Initialize()
{
	/*this->lifeSpan = 2.5f;
	this->maxProjectiles = 10.0f;*/
	
}

void ProjectileSystem::Release()
{

}
