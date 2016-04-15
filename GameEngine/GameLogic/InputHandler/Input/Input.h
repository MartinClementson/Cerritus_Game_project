#pragma once
#include "../InputHandler.h"
#include "../../../Source/LibIncluder.h"
#include "../../../Enumerations/Enumerations.h"

class Input
{
public:
	Input();
	~Input();
private:
	InputHandler* inputHandling;
public:
	void Initialize();
	void Release();
	bool IsKeyPressed(InputKeys key);
	bool IsKeyHeld(InputKeys key);
	DirectX::XMFLOAT2 GetMousePosition();
	bool isMouseClicked(InputKeys mouseKey);

};

