#pragma once
#include "../GameObject.h"

class Light :
	public GameObject
{
public:
	Light();
	~Light();
	void Initialize();
	void Release();
	void Update(double deltaTime);
	void Render();
private:
	//LightTypes lightID; //enum
	DirectX::XMFLOAT3 Color;
	float intensity;
};

