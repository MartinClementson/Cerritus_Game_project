#pragma once
#include "../../Source/LibIncluder.h"
#include "./GUIElement/GUIElement.h"
#include "SpriteFont.h"
class GUI : public GUIElement
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
	void setPos(XMFLOAT2 position);
	void setUI(UITextures texture);

private:
	UITextures texture;
	std::vector<GUIElement*>* items;

	DirectX::XMFLOAT2 size;
	DirectX::XMFLOAT2 position;
};

