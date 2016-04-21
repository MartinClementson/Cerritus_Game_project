#include "ProjectileSystem.h"
ProjectileSystem::ProjectileSystem()
{
	timeOffset = 0;
	maxProjectiles = 100;
}


ProjectileSystem::~ProjectileSystem()
{
	/*for (unsigned int i = 0; i < projectiles.size(); i++)
	{
		if (projectiles.at(i))
			delete projectiles.at(i);
	}*/

	/*for (unsigned int i = 0; i < LiveBullets.size(); i++)
	{
		delete LiveBullets.at(i);
	}*/
}


void ProjectileSystem::FireProjectile(XMFLOAT3 origin, XMFLOAT3 direction)
{ 
	
	//renderInfo = { origin, direction };
	

	for (unsigned int i = 0; i < 100; i++) // kurwa mac
	{
		if (!projectiles[i].GetFired())
		{
			projectiles[i].Initialize(origin, direction);
			break;
		}
		//aliveProjectiles[i+1];

	}
	/*
	//origin.x -= 1.0f;
	//projectiles[0].Initialize(origin, direction);
	//origin.x += 2.0f;
	//projectiles[1].Initialize(origin, direction);
	////projectiles[2].Initialize(origin, direction);*/

	//if (timeOffset > 0.2f)
	//{
	//	if (projectiles.size() >= maxProjectiles)
	//	{
	//		//delete projectiles.at(9);
	//	}
	//	else
	//	{
	//		projectiles.push_back(new Projectile(origin, direction));

	//	}
	//	timeOffset = 0;
	//}
	
}

void ProjectileSystem::UpdateProjectiles(double deltaTime)
{
	//projectiles->Update(deltaTime);
	//Render(1);
	timeOffset += 0.030f;
	if (timeOffset > 10)
		timeOffset = 10.0f;
	for (unsigned int i = 0; i < 100; i++)
	{
		if (projectiles[i].GetFired())
		{
			projectiles[i].Update(deltaTime);
			renderInfo = { projectiles[i].GetPos(), projectiles[i].GetDir() };
			graphics->QueueRender(&renderInfo);
		}

		if (projectiles[i].GetAge() >= lifeSpan)
		{
			projectiles[i].SetFired(false);
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
	//	//else
	//	//{
	//	//	//projectiles.at(i)->Initialize();
	//	//	DirectX::XMFLOAT3 tmp = projectiles[i].GetPos();
	//	//	tmp.x = tmp.x + projectiles[i].GetDir().x * projectiles[i].GetSpeed();
	//	//	tmp.z = tmp.z + projectiles[i].GetDir().z * projectiles[i].GetSpeed();
	//	//}
	//}
	

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


	//for (int i = 0; i < projectiles.size(); i++)
	//{

	//	if (projectiles.at(i)->GetFired())
	//	{
	//		//renderInfo = { projectiles.at(i)->GetPos(),projectiles.at(i)->GetDir() };
	//		graphics->QueueRender(&projectiles.at(i)->renderInfo);
	//	}
	//	
	//}
	for (unsigned int j = 0; j < 100; j++)
	{
		if (projectiles->GetFired())
		{
			//renderInfo = { projectiles[j].GetPos(), projectiles[j].GetDir() };
			graphics->QueueRender(&projectiles[j].renderInfo);
				
		}
	}
	
}
