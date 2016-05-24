#include "ProjectileSystem.h"



inline DirectX::XMFLOAT3 operator+(DirectX::XMFLOAT3 a, DirectX::XMFLOAT3 b) {
	DirectX::XMFLOAT3 result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;

	return result;
}
#define offsetX 1.052f
#define offsetY 0.0f
#define offsetZ 1.5f

float get_degrees(float radian);
inline float get_degrees(float radian)
{

	return (radian * 180) / XM_PI;
}

ProjectileSystem::ProjectileSystem()
{
	positionOffset = XMFLOAT3(offsetX, offsetY, offsetZ);
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
	for (unsigned int i = 0; (int)i < maxProjectiles; i++)

		delete projectiles[i];
}


void ProjectileSystem::FireProjectile(XMFLOAT3 origin, XMFLOAT3 direction)
{

	XMFLOAT3 originalDirection = direction;
	if (timeOffset > 0.2f)
	{
		if ((int)firedProjectiles >= maxProjectiles)
		{
			return;
		}
		else
		{
			/*for (unsigned int i = 0; (int)i < maxProjectiles; i++)
			{
*/
				//if (!projectiles[i]->GetFired())
				//{
					int xRoulette = rand() % 10 + 1; //left hand or right hand shot? who knows!
					int xMul = (xRoulette > 5 ? 1 : -1);

					positionOffset.x *= xMul;

					XMFLOAT3 rotation(0.0f, 0.0f, 0.0f); //Legacy, now rotation is handled in billboard shader
					if (GetUpgrade() == UpgradeType::ONE_SHOT)
					{
				
						projectiles[firedProjectiles]->Initialize(origin + positionOffset, direction, rotation);
						firedProjectiles++;
						audioManager->playShotSound();
						//break;
					}
					else if (GetUpgrade() == UpgradeType::TWO_SHOT)
					{
						XMVECTOR tmp = XMVector3TransformCoord(XMLoadFloat3(&direction), XMLoadFloat4x4(&rotationMatrix));
						XMStoreFloat3(&direction, tmp);
						
						projectiles[firedProjectiles]->Initialize(origin + positionOffset, direction, rotation);
						firedProjectiles++;
						///////////////////////////////////////////////////
						direction = originalDirection;

						tmp = XMVector3TransformCoord(XMLoadFloat3(&direction), XMLoadFloat4x4(&rotationMatrix2));
						XMStoreFloat3(&direction, tmp);
						
						projectiles[firedProjectiles]->Initialize(origin + positionOffset, direction, rotation);
						firedProjectiles++;
						audioManager->playShotSound();
						//break;
					}
					else if (GetUpgrade() == UpgradeType::THREE_SHOT)
					{
				
						projectiles[firedProjectiles]->Initialize(origin + positionOffset, direction, rotation);
						firedProjectiles++;
						////////////////////////////////////////////////////
						XMVECTOR tmp = XMVector3TransformCoord(XMLoadFloat3(&direction), XMLoadFloat4x4(&rotationMatrix));
						XMStoreFloat3(&direction, tmp);
						
						projectiles[firedProjectiles]->Initialize(origin + positionOffset, direction, rotation);
						firedProjectiles++;

						////////////////////////////////////////////////////
						direction = originalDirection;
						tmp = XMVector3TransformCoord(XMLoadFloat3(&direction), XMLoadFloat4x4(&rotationMatrix2));
						XMStoreFloat3(&direction, tmp);
				
						projectiles[firedProjectiles]->Initialize(origin + positionOffset, direction, rotation);
						firedProjectiles++;
						audioManager->playShotSound(); 
						//break;
					}
				//}
			//}
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
		XMStoreFloat4x4(&rotationMatrix,  XMMatrixRotationY(0.1f));
		XMStoreFloat4x4(&rotationMatrix2, XMMatrixRotationY(-0.1f));
	}
	else if (this->upgrade == UpgradeType::THREE_SHOT)
	{
		XMStoreFloat4x4(&rotationMatrix,  XMMatrixRotationY(0.2f));
		XMStoreFloat4x4(&rotationMatrix2, XMMatrixRotationY(-0.2f));
	}


}

UpgradeType ProjectileSystem::GetUpgrade()
{
	return upgrade;
}

void ProjectileSystem::Initialize(AudioManager* audioManager)
{

	this->audioManager = audioManager;
	graphics = Graphics::GetInstance();
	lifeSpan = 2.5f;
	//maxProjectiles = 100;

	//AntTweakBar::GetInstance()->addSlider("lifespan", *lifeSpan);
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