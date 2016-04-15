#pragma once
#include "LibIncluder.h"
#include "GUIElement.h"
class GUI
{
public:
	GUI();
	virtual ~GUI();
	void Initialize();
	void Release();
	void Update(double deltaTime);
	void Render();
private:
	std::vector<GUIElement*>* items;
	DirectX::XMFLOAT2 size;
	DirectX::XMFLOAT2 position;
};

