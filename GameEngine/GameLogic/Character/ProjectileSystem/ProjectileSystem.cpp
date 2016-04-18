#include "ProjectileSystem.h"



ProjectileSystem::ProjectileSystem()
{

}


ProjectileSystem::~ProjectileSystem()
{
	delete this->projectiles;
}

Projectile ProjectileSystem::FireProjectile(DirectX::XMFLOAT3 origin, DirectX::XMFLOAT3 direction)
{
	//position where the projectiles are fired from is the position of the player and the aim of the mouse i guess.
	//where are they shoot two

	projectiles->push_back();

}

void ProjectileSystem::UpdateProjectiles(double deltaTime)
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
