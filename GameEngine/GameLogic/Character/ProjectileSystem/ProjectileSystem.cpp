#include "ProjectileSystem.h"
ProjectileSystem::ProjectileSystem()
{

}


ProjectileSystem::~ProjectileSystem()
{
	
}


void ProjectileSystem::FireProjectile(XMFLOAT3 origin, XMFLOAT3 direction)
{ 
	
	if (projectiles.size() == maxProjectiles)
	{

		delete projectiles.at(0);
	}
	origin = { 0,0,0 };
	direction = { 0,0,0 };

	projectiles.push_back(new Projectile(origin, direction));
}


void ProjectileSystem::UpdateProjectiles(double deltaTime)
{
	for (int i = 0; i < projectiles.size(); i++)
	{
		projectiles.at(i)->Update(deltaTime);

		if (projectiles.at(i)->GetAge() >= lifeSpan)
		{
			delete projectiles.at(i);
		}
		else
		{
			DirectX::XMFLOAT3 tmp = projectiles.at(i)->GetPos();
			tmp.x = tmp.x + projectiles.at(i)->GetDir().x * projectiles.at(i)->GetSpeed();
			tmp.z = tmp.z + projectiles.at(i)->GetDir().z * projectiles.at(i)->GetSpeed();
		}
	}
}

void ProjectileSystem::Initialize()
{
	lifeSpan = 2.5f;
	maxProjectiles = 12;

}

void ProjectileSystem::Release()
{
	
}
