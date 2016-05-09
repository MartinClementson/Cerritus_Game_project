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
	UITextures getUI();
	XMFLOAT2 getPos();
	void setPos(XMFLOAT2 uv);
	void setUI(UITextures texture);

private:
	UITextures texture;
	std::vector<GUIElement*>* items;
	DirectX::XMFLOAT2 size;
	DirectX::XMFLOAT2 uv;
	//DirectX::XMFLOAT3 position;
	//DirectX::XMFLOAT3 rotation;
};

