#pragma once
#include "../../../Source/LibIncluder.h"
#include "../ProjectileSystem/Projectile/Projectile.h"
//#include "../Player/Player.h"
#include"../../../Structs/RenderInfo.h"
#include "../../../ResourceEngine/Graphics/Graphics.h"

class ProjectileSystem
{
public:
	ProjectileSystem();
	virtual ~ProjectileSystem();
	
private:
	Projectile projectiles[100];
	float lifeSpan;
	int maxProjectiles; 
	

public:
	void FireProjectile(DirectX::XMFLOAT3 origin, DirectX::XMFLOAT3 direction);
	void UpdateProjectile(double deltaTime);

	RenderInfoProjectile renderInfo;
	Graphics* graphics;

	void Initialize();
	void Release();
	void Render(int i);
};