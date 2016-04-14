#pragma once
#include "LibIncluder.h"
class Character
{
public:
	Character();
	~Character();
private:
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 rotation;

	float movementSpeed, health, damage;
	//Animation* animations
	//Model* meshes
public:
	virtual void Initialize();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	//Collision();
};

