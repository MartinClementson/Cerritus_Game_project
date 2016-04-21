#include "ProjectileSystem.h"
ProjectileSystem::ProjectileSystem()
{

}


ProjectileSystem::~ProjectileSystem()
{
}


void ProjectileSystem::FireProjectile(XMFLOAT3 origin, XMFLOAT3 direction)
{ 
	
	//renderInfo = { origin, direction };

	for (unsigned int i = 0; i < 100; i++)
	{
		if (!projectiles[i].GetFired())
		{
			projectiles[i].Initialize(origin, direction);
			break;
		}
	}



	//if (projectiles >= maxProjectiles)
	//{
	//	//delete projectiles.at(9);
	//}
	//else
	//{

	//	//origin = { 0,0,0 };
	//	//direction = { 0,0,0 };
	


	//	
	//}
}
/// is fired array

void ProjectileSystem::UpdateProjectiles(double deltaTime)
{
	//projectiles->Update(deltaTime);
	//Render(1);
	for (unsigned int i = 0; i < 100; i++)
	{
		if (projectiles[i].GetFired())
		{
			projectiles[i].Update(deltaTime);

		/*	if (projectiles[i].GetAge() >= lifeSpan)
			{
				projectiles[i].SetFired(false);
			}*/
		}
	}

	//for (int i = 0; i < projectiles.size(); i++)
	//{

	//	projectiles.at(i)->Update(deltaTime);

	//	if (projectiles.at(i)->GetAge() >= lifeSpan)
	//	{
	//		delete projectiles.at(i);
	//		projectiles.erase(projectiles.begin());
	//		projectiles.shrink_to_fit();
	//	}
	//	else
	//	{
	//		//projectiles.at(i)->Initialize();
	//		DirectX::XMFLOAT3 tmp = projectiles[i].GetPos();
	//		tmp.x = tmp.x + projectiles[i].GetDir().x * projectiles[i].GetSpeed();
	//		tmp.z = tmp.z + projectiles[i].GetDir().z * projectiles[i].GetSpeed();
	//	}
	//}
	//

}

void ProjectileSystem::Initialize()
{

	graphics = Graphics::GetInstance();
	lifeSpan = 2.5f;
	//maxProjectiles = 100;
	

}

void ProjectileSystem::Release()
{
	
	
}

void ProjectileSystem::Render()
{
	for (unsigned int j = 0; j < 100; j++)
	{
		if (projectiles[j].GetFired())
		{
			renderInfo = { projectiles[j].GetPos(), projectiles[j].GetDir() };
			graphics->QueueRender(&renderInfo);
		}
	}
	

}
