#pragma once
#include "../../Source/LibIncluder.h"
#include "../../Source/Constants.h"
#include "../../Enumerations/Enumerations.h"
#include "../../Structs/DataTypes.h"
#include "../../ResourceEngine/anttweakbar/AntTweakBar.h"

using namespace DirectX;

class InputHandler
{
private:
	LPDIRECTINPUT8 input;
	LPDIRECTINPUTDEVICE8 keyboard;
	LPDIRECTINPUTDEVICE8 mouse;
	unsigned char keyboardState[256];
	DIMOUSESTATE mouseState;
	
	float mouseX, mouseY;
	float lastMouseX, lastMouseY;

	bool isLshiftPressed;

private:
	void ProcessInput();
	bool ReadKeyboard();
	bool ReadMouse();
	InputHandler();


	HWND* hwndP;
public:
	~InputHandler();
	LPDIRECTINPUTDEVICE8 GetMouse();

	bool Initialize(HWND* hwndP, HINSTANCE* hInstance);
	void Release();

	bool IsKeyPressed(InputKeys* key);
	bool IsKeyHeld(InputKeys* key);
	XMFLOAT2 GetMousePosition();
	bool isMouseClicked(InputKeys* mouseKey);
	void SetMouseVisibility(bool x);
	static InputHandler* GetInstance();
	
};

