#pragma once
#include "../../Source/LibIncluder.h"
#include "./GUIElement/GUIElement.h"




class GUI
{
public:
	
	/*struct UV
	{
		XMFLOAT2 UV[4];
	};*/
	
	GUI();
	virtual ~GUI();
	void Initialize();
	void Release();
	void Update(double deltaTime);
	void Render();
	RenderInfoUI renderInfo;
	Graphics* grapichs;
	UITextures getUI();
	XMFLOAT3 getPos();
	void setPos(XMFLOAT3 uv);
	void setUI(UITextures texture);
	void setUINR(UiNumbers numbers);


private:
	UITextures texture;
	UiNumbers numbers;
	std::vector<GUI>*items;
	//std::vector<GUIElement*>* items;
	DirectX::XMFLOAT3 size;
	DirectX::XMFLOAT3 uv;
};

