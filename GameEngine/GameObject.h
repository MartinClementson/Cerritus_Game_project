#pragma once
#include "LibIncluder.h"

class GameObject
{
public:
	GameObject();
	~GameObject();
private:
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 rotation;
	DirectX::XMFLOAT3 scale;
	DirectX::XMFLOAT3 pivot;
public:
	virtual void Initialize();
	virtual void Release();
	virtual void Update(double deltaTime);
	virtual void Render();

};

