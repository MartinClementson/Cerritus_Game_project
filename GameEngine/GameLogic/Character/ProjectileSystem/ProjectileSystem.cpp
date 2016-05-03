#include "ProjectileSystem.h"
float get_degrees(float radian);
inline float get_degrees(float radian)
{

	return (radian * 180) / XM_PI;
}

ProjectileSystem::ProjectileSystem()
{
	timeOffset = 0;
	maxProjectiles = 200;
	firedProjectiles = 0;
	for (unsigned int i = 0; (int)i < maxProjectiles; i++)
		projectiles[i] = new Projectile;
}


ProjectileSystem::~ProjectileSystem()
{
	/*for (unsigned int i = 0; i < projectiles.size(); i++)
	{
		if (projectiles.at(i))
			delete projectiles.at(i);
	}*/
	for (unsigned int i = 0; i < maxProjectiles; i++)
		delete projectiles[i];
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

	XMFLOAT3 originalDirection = direction;
	if (timeOffset > 0.2f)
	{
		if ((int)firedProjectiles >= maxProjectiles)
		{
			//delete projectiles.at(9);
		}
		else
		{
			for (unsigned int i = 0; (int)i < maxProjectiles; i++)
			{
#pragma region Calculate rotation of projectile mesh
				if (!projectiles[i]->GetFired())
				{
					XMFLOAT3 rotation(0.0f, 0.0f, 0.0f);

					// placeholder direction is now (0,0,1)

					/*	result = dot product of direction and placeholder direction
					acos(result)
					*/
					if (GetUpgrade() == UpgradeType::ONE_SHOT)
					{
						//XMVECTOR shotDirection = XMVectorSet(direction.x, 0.0f, direction.z, 0.0f);
						//XMVECTOR meshDirection = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);


						////Calculate angle between meshDir and shotDir
						//float cosAngle = XMVector3Dot(shotDirection, meshDirection).m128_f32[0];
						//float angle = acos(cosAngle);
						//float degrees = get_degrees(angle);
						//////////////////////////////////////////////////////

						//if (direction.x < 0)
						//	degrees = -degrees;

						//rotation.y = degrees;


#pragma endregion
						projectiles[i]->Initialize(origin, direction, rotation);
						firedProjectiles++;
						//projectiles.push_back(new Projectile(origin, direction, rotation));
						break;
					}
					else if (GetUpgrade() == UpgradeType::TWO_SHOT)
					{
						XMVECTOR tmp = XMVector3TransformCoord(XMLoadFloat3(&direction), XMLoadFloat4x4(&rotationMatrix));
						XMStoreFloat3(&direction, tmp);
						//XMVECTOR shotDirection = XMVectorSet(direction.x, 0.0f, direction.z, 0.0f);
						//XMVECTOR meshDirection = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);


						////Calculate angle between meshDir and shotDir
						//float cosAngle = XMVector3Dot(shotDirection, meshDirection).m128_f32[0];
						//float angle = acos(cosAngle);
						//float degrees = get_degrees(angle);
						//////////////////////////////////////////////////////

						//if (direction.x < 0)
						//	degrees = -degrees;

						//rotation.y = degrees;
						//projectiles.push_back(new Projectile(origin, direction, rotation));
						projectiles[i]->Initialize(origin, direction, rotation);
						firedProjectiles++;
						///////////////////////////////////////////////////
						direction = originalDirection;

						tmp = XMVector3TransformCoord(XMLoadFloat3(&direction), XMLoadFloat4x4(&rotationMatrix2));
						XMStoreFloat3(&direction, tmp);
						//shotDirection = XMVectorSet(direction.x, 0.0f, direction.z, 0.0f);
						//meshDirection = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);




						////Calculate angle between meshDir and shotDir
						//cosAngle = XMVector3Dot(shotDirection, meshDirection).m128_f32[0];

						//angle = acos(cosAngle);
						//degrees = get_degrees(angle);
						//////////////////////////////////////////////////////

						//if (direction.x < 0)
						//	degrees = -degrees;

						//rotation.y = degrees;


						//projectiles.push_back(new Projectile(origin, direction, rotation));
						projectiles[i+1]->Initialize(origin, direction, rotation);
						firedProjectiles++;
						break;
					}
					else if (GetUpgrade() == UpgradeType::THREE_SHOT)
					{


						XMVECTOR shotDirection = XMVectorSet(direction.x, 0.0f, direction.z, 0.0f);
						XMVECTOR meshDirection = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);


						//Calculate angle between meshDir and shotDir
						float cosAngle = XMVector3Dot(shotDirection, meshDirection).m128_f32[0];
						float angle = acos(cosAngle);
						float degrees = get_degrees(angle);
						////////////////////////////////////////////////////

						if (direction.x < 0)
							degrees = -degrees;

						rotation.y = degrees;


#pragma endregion

						//projectiles.push_back(new Projectile(origin, direction, rotation));
						projectiles[i]->Initialize(origin, direction, rotation);
						firedProjectiles++;
						////////////////////////////////////////////////////
						XMVECTOR tmp = XMVector3TransformCoord(XMLoadFloat3(&direction), XMLoadFloat4x4(&rotationMatrix));
						XMStoreFloat3(&direction, tmp);
						shotDirection = XMVectorSet(direction.x, 0.0f, direction.z, 0.0f);
						meshDirection = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);




						//Calculate angle between meshDir and shotDir
						cosAngle = XMVector3Dot(shotDirection, meshDirection).m128_f32[0];

						angle = acos(cosAngle);
						degrees = get_degrees(angle);
						////////////////////////////////////////////////////

						if (direction.x < 0)
							degrees = -degrees;

						rotation.y = degrees;


						//projectiles.push_back(new Projectile(origin, direction, rotation));
						projectiles[i+1]->Initialize(origin, direction, rotation);
						firedProjectiles++;


						////////////////////////////////////////////////////
						direction = originalDirection;
						tmp = XMVector3TransformCoord(XMLoadFloat3(&direction), XMLoadFloat4x4(&rotationMatrix2));
						XMStoreFloat3(&direction, tmp);
						shotDirection = XMVectorSet(direction.x, 0.0f, direction.z, 0.0f);
						meshDirection = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);




						//Calculate angle between meshDir and shotDir
						cosAngle = XMVector3Dot(shotDirection, meshDirection).m128_f32[0];

						angle = acos(cosAngle);
						degrees = get_degrees(angle);
						////////////////////////////////////////////////////

						if (direction.x < 0)
							degrees = -degrees;

						rotation.y = degrees;


						//projectiles.push_back(new Projectile(origin, direction, rotation));
						projectiles[i+2]->Initialize(origin, direction, rotation);
						firedProjectiles++;
						break;
					}
				}
			}
			timeOffset = 0;
		}
	}

}

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
	timeOffset += 2.0f * float(deltaTime);
	if (timeOffset > 10)
		timeOffset = 10.0f;
	for (size_t i = 0; i < firedProjectiles; i++)
	{


		projectiles[i]->Update(deltaTime);

		if (projectiles[i]->GetAge() >= lifeSpan || projectiles[i]->GetFired()==false)
		{
			DeleteProjectile((int)i);
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
	/*delete projectiles.at(index);
	projectiles.erase(projectiles.begin()+index);
	projectiles.shrink_to_fit();*/
  	projectiles[index]->SetFired(false);
	//if (firedProjectiles != 0)
	firedProjectiles--;

	//swapping
	Projectile *temp;
	temp							  = projectiles[index];
	projectiles[index]				  = projectiles[firedProjectiles];
	projectiles[firedProjectiles]     = temp;
}

void ProjectileSystem::SetUpgrade(UpgradeType upgrade)
{
	this->upgrade = upgrade;

	if (this->upgrade == UpgradeType::ONE_SHOT)
	{

	}
	else if (this->upgrade == UpgradeType::TWO_SHOT)
	{
		XMStoreFloat4x4(&rotationMatrix, XMMatrixRotationY(0.1f));
		XMStoreFloat4x4(&rotationMatrix2, XMMatrixRotationY(-0.1f));
	}
	else if (this->upgrade == UpgradeType::THREE_SHOT)
	{
		XMStoreFloat4x4(&rotationMatrix, XMMatrixRotationY(0.4f));
		XMStoreFloat4x4(&rotationMatrix2, XMMatrixRotationY(-0.4f));
	}

	
}

UpgradeType ProjectileSystem::GetUpgrade()
{
	return upgrade;
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


	for (size_t i = 0; i < firedProjectiles; i++)
	{

		if (projectiles[i]->GetFired())
		{
			//renderInfo = { projectiles.at(i)->GetPos(),projectiles.at(i)->GetDir() };
			graphics->QueueRender(&projectiles[i]->renderInfo);
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