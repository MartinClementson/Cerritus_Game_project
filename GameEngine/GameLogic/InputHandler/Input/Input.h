#pragma once
#include "../InputHandler.h"
#include "../../../Source/LibIncluder.h"
#include "../../../Enumerations/Enumerations.h"

using namespace DirectX;
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
	XMFLOAT2 GetMousePosition();
	bool isMouseClicked(InputKeys mouseKey);
	void SetMouseVisibility(bool x) { inputHandling->SetMouseVisibility(x); };

	static Input* GetInstance();
	LPDIRECTINPUTDEVICE8 GetMouse();
};

