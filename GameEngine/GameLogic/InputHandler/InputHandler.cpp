#include "InputHandler.h"



InputHandler::InputHandler()
{
}


InputHandler::~InputHandler()
{
}

void InputHandler::ProcessInput()
{
}

bool InputHandler::ReadKeyboard()
{
	return false;
}

bool InputHandler::ReadMouse()
{
	return false;
}

void InputHandler::Initialize(HINSTANCE hInstance)
{
	HRESULT hr = DirectInput8Create(
		hInstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&input,
		NULL);

	hr = input->CreateDevice(GUID_SysKeyboard,
		&keyboard,
		NULL);

	hr = input->CreateDevice(GUID_SysMouse,
		&mouse,
		NULL);

	hr = keyboard->SetDataFormat(&c_dfDIKeyboard);
	hr = keyboard->SetCooperativeLevel(hwndP, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	hr = mouse->SetDataFormat(&c_dfDIMouse);
	hr = mouse->SetCooperativeLevel(hwndP, DISCL_EXCLUSIVE | DISCL_NOWINKEY | DISCL_FOREGROUND);
}

void InputHandler::Release()
{
}
	

bool InputHandler::IsKeyPressed(InputKeys* key)
{
	keyboard->Acquire();

	keyboard->GetDeviceState(sizeof(keyboardState), (LPVOID)&keyboardState);

	if (key[0] == KEY_W && keyboardState[DIK_W]&&0x80)
	{
		return true;
	}
	else if (key[0] == KEY_A && keyboardState[DIK_A && 0x80])
	{
		return true;
	}
	else if (key[0] == KEY_D && keyboardState[DIK_D && 0x80])
	{
		return true;
	}
	else if (key[0] == KEY_S && keyboardState[DIK_S && 0x80])
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool InputHandler::IsKeyHeld(InputKeys* key)
{
	return false;
}

DirectX::XMFLOAT2 InputHandler::GetMousePosition()
{
	return DirectX::XMFLOAT2();
}

bool InputHandler::isMouseClicked(InputKeys* mouseKey)
{
	mouse->Acquire();
	mouse->GetDeviceState(sizeof(DIMOUSESTATE), &mouseState);
	return false;
}

InputHandler * InputHandler::GetInstance()
{
	static InputHandler instance;
	return &instance;
}
