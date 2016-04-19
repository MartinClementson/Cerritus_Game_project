#include "InputHandler.h"



InputHandler::InputHandler()
{
}


InputHandler::~InputHandler()
{
	keyboard->Unacquire();
	mouse->Unacquire();
	input->Release();
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

bool InputHandler::Initialize(HWND* hwndP ,HINSTANCE* hInstance)
{
	//keyboard->Acquire();

	HRESULT hr = DirectInput8Create(
		*hInstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&input,
		NULL);
	if (FAILED(hr))
	{
		return false;
	}

	hr = input->CreateDevice(GUID_SysKeyboard, &this->keyboard, NULL);
	if (FAILED(hr))
	{
		return false;
	}
	hr = input->CreateDevice(GUID_SysMouse,
		&mouse,
		NULL);
	if (FAILED(hr))
	{
		return false;
	}

	hr = keyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr))
	{
		return false;
	}

	hr = mouse->SetDataFormat(&c_dfDIMouse);
	if (FAILED(hr))
	{
		return false;
	}

	hr = keyboard->SetCooperativeLevel(*hwndP, DISCL_BACKGROUND| DISCL_NONEXCLUSIVE);
	if (FAILED(hr))
	{
		return false;
	}

	hr = mouse->SetCooperativeLevel(*hwndP, DISCL_EXCLUSIVE | DISCL_NOWINKEY | DISCL_FOREGROUND);
	if (FAILED(hr))
	{
		return false;
	}


	hr = keyboard->Acquire();
	if (FAILED(hr))
	{
		hr = keyboard->Acquire();
		//Re-acquire helps
	}
	return true;
}

void InputHandler::Release()
{
}
	

bool InputHandler::IsKeyPressed(InputKeys* key)
{

	keyboard->GetDeviceState(sizeof(keyboardState), (LPVOID)&keyboardState);

	if (key[0] == KEY_W && keyboardState[DIK_W])
	{
		return true;
	}
	else if (key[0] == KEY_A && keyboardState[DIK_A])
	{
		return true;
	}
	else if (key[0] == KEY_D && keyboardState[DIK_D])
	{
		return true;
	}
	else if (key[0] == KEY_S && keyboardState[DIK_S])
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
