#pragma once
#include "../InputHandler.h"
#include "../../../Source/LibIncluder.h"
#include "../../../Enumerations/Enumerations.h"

class Input
{
public:
	virtual ~Input();
private:
	InputHandler* inputHandling;
	Input();
public:
	void Initialize();
	void Release();
	bool IsKeyPressed(InputKeys key);
	bool IsKeyHeld(InputKeys key);
	DirectX::XMFLOAT2 GetMousePosition();
	bool isMouseClicked(InputKeys mouseKey);

	static Input* GetInstance();
};

