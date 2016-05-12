#pragma once

#include "../GameObject.h"
#include "../../../../Structs/RenderInfo.h"
#include "../../../../ResourceEngine/Graphics/Graphics.h"

using namespace DirectX;
using namespace std;

class Pickup :
	public GameObject
{
private:
	Pickup();

	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 rotation;
	DirectX::XMFLOAT3 scale;
	DirectX::XMFLOAT3 pivot;
	RenderInfoObject RenderInfo;
	Graphics * graphics;
	float radius;
	bool isActive;
	bool down;
public:
	Pickup(XMFLOAT3 pos);
	virtual ~Pickup();
	virtual void Initialize();
	virtual void Release();
	virtual void Update(double deltaTime);
	virtual void Render();
	XMFLOAT3 GetPosition();
	void SetPosition(XMFLOAT3 pos);
	float GetRadius();
	bool GetIsActive();
	void SetIsActive(bool active);
};

