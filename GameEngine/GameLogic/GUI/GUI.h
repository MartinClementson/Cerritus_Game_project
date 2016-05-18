#pragma once
#include "../../Source/LibIncluder.h"
#include "./GUIElement/GUIElement.h"




class GUI
{
public:
	GUI();
	GUI(UITextures texture);
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
	//void setBlyat(UITextures blyat, UiNumbers numberino);
	void poop();


private:
	UITextures texture;
	UiNumbers numbers;
	/*UITextures texture1;*/
	//HUDEN blyat;
	//std::vector<GUI*> items;
	std::vector<GUIElement*>* items;
	DirectX::XMFLOAT3 size;
	DirectX::XMFLOAT3 uv;
};

