#pragma once
#include "InputHandler.h"
#include "LibIncluder.h"
#include "Enumerations.h"

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

