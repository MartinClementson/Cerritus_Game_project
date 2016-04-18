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
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 rotation;

	float movementSpeed, health, damage;
	Graphics* graphics;
	Animation* animations;
	Model* meshes;
public:
	virtual void Initialize();
	virtual void Release();
	virtual void Update(double deltaTime);
	virtual void Render();

	//Collision();
};

