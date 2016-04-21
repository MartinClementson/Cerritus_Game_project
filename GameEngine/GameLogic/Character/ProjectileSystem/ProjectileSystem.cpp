#include "ProjectileSystem.h"
float get_degrees(float radian);
inline float get_degrees(float radian)
{

	return (radian * 180) / XM_PI;
}
ProjectileSystem::ProjectileSystem()
{
	timeOffset = 0;
	maxProjectiles = 100;
}


ProjectileSystem::~ProjectileSystem()
{
	for (unsigned int i = 0; i < projectiles.size(); i++)
	{
		if (projectiles.at(i))
			delete projectiles.at(i);
	}
}


void ProjectileSystem::FireProjectile(XMFLOAT3 origin, XMFLOAT3 direction)
{ 
	
	//renderInfo = { origin, direction };

	//for (unsigned int i = 0; i < 100; i++) // kurwa mac
	//{
	//	if (!projectiles[i].GetFired())
	//	{
	//		projectiles[i].Initialize(origin, direction);
	//		break;
	//	}

	//}

	//origin.x -= 1.0f;
	//projectiles[0].Initialize(origin, direction);
	//origin.x += 2.0f;
	//projectiles[1].Initialize(origin, direction);
	////projectiles[2].Initialize(origin, direction);
	if (timeOffset > 0.2f)
	{
		if ((int)projectiles.size() >= maxProjectiles)
		{
			//delete projectiles.at(9);
		}
		else
		{

#pragma region Calculate rotation of projectile mesh
			XMFLOAT3 rotation(90.0f,0.0f,0.0f);
			
			
			// placeholder direction is now (0,0,1)

			/*	result = dot product of direction and placeholder direction
			acos(result)
			*/

			XMVECTOR shotDirection   = XMVectorSet(direction.x, 0.0f, direction.z, 0.0f);
			XMVECTOR meshDirection   = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);

			
			//Calculate angle between meshDir and shotDir
			float cosAngle			 = XMVector3Dot(shotDirection, meshDirection).m128_f32[0];
			float angle				 = acos(cosAngle);
			float degrees			 = get_degrees(angle);
			////////////////////////////////////////////////////

			if (direction.x < 0)
				degrees = -degrees;

			rotation.y				 = degrees;


#pragma endregion


			projectiles.push_back(new Projectile(origin, direction,rotation));

		}
		timeOffset = 0;
	}
	
}
/// is fired array

void ProjectileSystem::UpdateProjectiles(double deltaTime)
{
	//projectiles->Update(deltaTime);
	//Render(1);
	//for (unsigned int i = 0; i < 100; i++)
	//{
	//	if (projectiles[i].GetFired())
	//	{
	//		projectiles[i].Update(deltaTime);
	//		//renderInfo = { projectiles[i].GetPos(), projectiles[i].GetDir() };
	//		//graphics->QueueRender(&renderInfo);
	//	}

	//	/*	if (projectiles[i].GetAge() >= lifeSpan)
	//		{
	//			projectiles[i].SetFired(false);
	//		}*/
	//	
	//}
	timeOffset += 0.030f;
	if (timeOffset > 10)
		timeOffset = 10.0f;
	for (size_t i = 0; i < projectiles.size(); i++)
	{

		projectiles.at(i)->Update(deltaTime);

		if (projectiles.at(i)->GetAge() >= lifeSpan)
		{
			DeleteProjectile(i);
			
		}
		//else
		//{
		//	//projectiles.at(i)->Initialize();
		//	DirectX::XMFLOAT3 tmp = projectiles[i].GetPos();
		//	tmp.x = tmp.x + projectiles[i].GetDir().x * projectiles[i].GetSpeed();
		//	tmp.z = tmp.z + projectiles[i].GetDir().z * projectiles[i].GetSpeed();
		//}
	}
	

}

void ProjectileSystem::DeleteProjectile(int index)
{
	delete projectiles.at(index);
	projectiles.erase(projectiles.begin());
	projectiles.shrink_to_fit();
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


	for (size_t i = 0; i < projectiles.size(); i++)
	{

		if (projectiles.at(i)->GetFired())
		{
			//renderInfo = { projectiles.at(i)->GetPos(),projectiles.at(i)->GetDir() };
			graphics->QueueRender(&projectiles.at(i)->renderInfo);
		}
		
	}
	/*for (unsigned int j = 0; j < 3; j++)
	{
		if (projectiles->GetFired())
		{
			renderInfo = { projectiles[j].GetPos(), projectiles[j].GetDir() };
			graphics->QueueRender(&renderInfo);
				
		}
	}*/
	
}
