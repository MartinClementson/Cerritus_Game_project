#pragma once
#include "../../../Source/LibIncluder.h"
class GUIElement
{
public:
	GUIElement();
	virtual ~GUIElement();
	void Initialize();
	void Release();
	void Update(double deltaTime);
	void Render();
private:
	DirectX::XMFLOAT2 size;
	DirectX::XMFLOAT2 position;
};

