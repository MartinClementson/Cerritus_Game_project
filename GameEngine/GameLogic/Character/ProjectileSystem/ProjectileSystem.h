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
	

	//Projectile projectiles[100];
	//Projectile firedProjectiles[100];
	float lifeSpan;
	int maxProjectiles;
	RenderInfoObject renderInfo;
	float timeOffset;

public:
	void FireProjectile(DirectX::XMFLOAT3 origin, DirectX::XMFLOAT3 direction);
	void UpdateProjectiles(double deltaTime);

	
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