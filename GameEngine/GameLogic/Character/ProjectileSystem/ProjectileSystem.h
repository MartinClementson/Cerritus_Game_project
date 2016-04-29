#pragma once
#include "../../../Source/LibIncluder.h"
#include "../ProjectileSystem/Projectile/Projectile.h"
//#include "../Player/Player.h"
#include"../../../Structs/RenderInfo.h"
#include "../../../ResourceEngine/Graphics/Graphics.h"


using namespace DirectX;

class ProjectileSystem
{
public:
	ProjectileSystem();
	virtual ~ProjectileSystem();

private:

	XMFLOAT4X4 rotationMatrix;
	XMFLOAT4X4 rotationMatrix2;
	//Projectile projectiles[100];
	//Projectile firedProjectiles[100];
	float lifeSpan;
	int maxProjectiles;
	RenderInfoObject renderInfo;
	float timeOffset;
	UpgradeType upgrade;

public:
	void FireProjectile(DirectX::XMFLOAT3 origin, DirectX::XMFLOAT3 direction);
	void UpdateProjectiles(double deltaTime);
	void DeleteProjectile(int index);
	void SetUpgrade(UpgradeType upgrade);
	UpgradeType GetUpgrade();


	Graphics* graphics;

	std::vector<Projectile*> projectiles;
	//float lifeSpan; //travel time
	//int maxProjectiles; // amout of projectiles
	//Player* pos;

public:


	void Initialize();
	void Release();
	void Render();
};