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
	
	for (unsigned int i = 0; i < maxProjectiles; i++)
		delete projectiles[i];
}


void ProjectileSystem::FireProjectile(XMFLOAT3 origin, XMFLOAT3 direction)
{

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

				if (!projectiles[i]->GetFired())
				{
					XMFLOAT3 rotation(0.0f, 0.0f, 0.0f); //Legacy, now rotation is handled in billboard shader
					if (GetUpgrade() == UpgradeType::ONE_SHOT)
					{
				
						projectiles[i]->Initialize(origin, direction, rotation);
						firedProjectiles++;
						
						break;
					}
					else if (GetUpgrade() == UpgradeType::TWO_SHOT)
					{
						XMVECTOR tmp = XMVector3TransformCoord(XMLoadFloat3(&direction), XMLoadFloat4x4(&rotationMatrix));
						XMStoreFloat3(&direction, tmp);
						
						projectiles[i]->Initialize(origin, direction, rotation);
						firedProjectiles++;
						///////////////////////////////////////////////////
						direction = originalDirection;

						tmp = XMVector3TransformCoord(XMLoadFloat3(&direction), XMLoadFloat4x4(&rotationMatrix2));
						XMStoreFloat3(&direction, tmp);
						
						projectiles[i+1]->Initialize(origin, direction, rotation);
						firedProjectiles++;
						break;
					}
					else if (GetUpgrade() == UpgradeType::THREE_SHOT)
					{
				
						projectiles[i]->Initialize(origin, direction, rotation);
						firedProjectiles++;
						////////////////////////////////////////////////////
						XMVECTOR tmp = XMVector3TransformCoord(XMLoadFloat3(&direction), XMLoadFloat4x4(&rotationMatrix));
						XMStoreFloat3(&direction, tmp);
						
						projectiles[i+1]->Initialize(origin, direction, rotation);
						firedProjectiles++;

						////////////////////////////////////////////////////
						direction = originalDirection;
						tmp = XMVector3TransformCoord(XMLoadFloat3(&direction), XMLoadFloat4x4(&rotationMatrix2));
						XMStoreFloat3(&direction, tmp);
				
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
	
	}


}

void ProjectileSystem::DeleteProjectile(int index)
{
	
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
}