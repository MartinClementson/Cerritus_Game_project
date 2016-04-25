#pragma once
#include "../../Source/LibIncluder.h"
#include "../Animation/Animation.h"
#include "../Scene/GameObject/Model/Model.h"
#include "../../ResourceEngine/Graphics/Graphics.h"

class Character
{
public:
	Character();
	virtual ~Character();

protected:
	XMFLOAT3 rotation;
	float radius, radius2;

	float health, damage;
	bool dead, idle, active;
	Graphics* graphics;
	Animation* animations;
	Model* meshes;

	

public:
	XMFLOAT3 position;

	float movementSpeed;

	virtual void Initialize();
	virtual void Release();
	virtual void Update(double deltaTime);
	virtual void Render();
	float DoT;
	float DoTDur;

	//Collision();
};

