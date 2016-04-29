#pragma once
#include "../../Source/LibIncluder.h"
#include "./GUIElement/GUIElement.h"
class GUI
{
public:
	GUI();
	virtual ~GUI();
	void Initialize();
	void Release();
	void Update(double deltaTime);
	void Render();
	RenderInfoUI renderInfo;
	Graphics* grapichs;
private:
	UITextures texture;
	std::vector<GUIElement*>* items;
	DirectX::XMFLOAT3 size;
	DirectX::XMFLOAT3 position;
	//DirectX::XMFLOAT3 position;
	//DirectX::XMFLOAT3 rotation;
};

