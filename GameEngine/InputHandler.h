#pragma once
class InputHandler
{
public:
	InputHandler();
	~InputHandler();
private:
	//LPDIRECTINPUT8 input;
	//LPDIRECTINPUTDEVICE8 keyboard;
	//LPDIRECTINPUTDEVICE8 mouse;
	unsigned char keyboardState[256];
	//DIMOUSESTATE mouseState;

	float mouseX, mouseY;
	float lastMouseX, lastMouseY;

private:
	void ProcessInput();
	bool ReadKeyboard();
	bool ReadMouse();

	//HWND hwndP;
public:

};

