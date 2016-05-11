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
	RenderInfoUI swagitt;
	int amount;
	Graphics* grapichs;
	UITextures getUI();
	XMFLOAT2 getPos();
	void setPos(XMFLOAT2 uv);
	void setUI(UITextures texture);
	void setUINR(UiNumbers numbers);
	/*std::vector<UV*> UVs;
	XMFLOAT2 vtx[4];*/

private:
	UITextures texture;
	UiNumbers numbers;
	std::vector<GUIElement*>* items;
	DirectX::XMFLOAT2 size;
	DirectX::XMFLOAT2 uv;
	//DirectX::XMFLOAT3 position;
	//DirectX::XMFLOAT3 rotation;
};

