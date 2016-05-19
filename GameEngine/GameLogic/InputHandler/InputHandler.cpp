#include "InputHandler.h"



InputHandler::InputHandler()
{
}

LPDIRECTINPUTDEVICE8 InputHandler::GetMouse()
{
	return mouse;
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
	this->hwndP = hwndP;
	isLshiftPressed = false;
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

	hr = mouse->SetCooperativeLevel(*hwndP, DISCL_NONEXCLUSIVE | DISCL_NOWINKEY | DISCL_FOREGROUND);
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

	hr = mouse->Acquire();
	if (FAILED(hr))
	{
		hr = mouse->Acquire();
	}

	ShowCursor(TRUE);
	
	SetCursor(LoadCursor(NULL, IDC_CROSS));
	
	
	
	return true;
}

void InputHandler::Release()
{
}
	

bool InputHandler::IsKeyPressed(InputKeys* key)
{

	keyboard->GetDeviceState(sizeof(keyboardState), (LPVOID)&keyboardState);

	if (*key == KEY_W && keyboardState[DIK_W])
	{
		return true;
	}
	else if (*key == KEY_A && keyboardState[DIK_A])
	{
		return true;
	}
	else if (*key == KEY_D && keyboardState[DIK_D])
	{
		return true;
	}
	else if (*key == KEY_S && keyboardState[DIK_S])
	{
		return true;
	}
	else if (*key == KEY_Q && keyboardState[DIK_Q])
	{
		
		return true;
	}
	else if (*key == KEY_LEFT && keyboardState[DIK_LEFT])
	{
		return true;
	}
	else if (*key == KEY_SPACE && keyboardState[DIK_SPACE])
	{
		return true;
	}
	else if (*key == KEY_ENTER && keyboardState[DIK_RETURN])
	{
		return true;
	}
	else if (*key == KEY_P && keyboardState[DIK_P])
	{
		return true;
	}

	else if (*key == KEY_Z && keyboardState[DIK_Z])
	{
		return true;
	}
	else if (*key == KEY_X && keyboardState[DIK_X])
	{
		//mouse->Unacquire();
		//mouse->SetCooperativeLevel(*hwndP, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
		
		return true;
	}
	else if (*key == KEY_C && keyboardState[DIK_C])
	{
		return true;
	}
	else if (*key == KEY_ESC && keyboardState[DIK_ESCAPE])
	{
		return true;
	}
	else if (*key == KEY_LSHIFT && keyboardState[DIK_LSHIFT])
	{
		isLshiftPressed = true;
		return true;
	}
	else if (*key == KEY_UP && keyboardState[DIK_UP])
	{
		return true;
	}
	else if (*key == KEY_DOWN && keyboardState[DIK_DOWN])
	{
		return true;
	}
	else if (*key == KEY_LEFT && keyboardState[DIK_LEFT])
	{
		return true;
	}
	else if (*key == KEY_RIGHT && keyboardState[DIK_RIGHT])
	{
		return true;
	}
	else if (*key == KEY_PGUP && keyboardState[DIK_PGUP])
	{
		return true;
	}
	else if (*key == KEY_PGDWN && keyboardState[DIK_PGDN])
	{
		return true;
	}
	else
	{
		isLshiftPressed = false;
		return false;
	}
}

bool InputHandler::IsKeyHeld(InputKeys* key)
{
	if (isLshiftPressed == true)
	{
		return true;
	}
	return false;
}

XMFLOAT2 InputHandler::GetMousePosition()
{

	POINT point;
	ShowCursor(TRUE);

	GetCursorPos(&point);
	ScreenToClient(*this->hwndP, &point);
		
	mouseX = (float)point.x;
	mouseY = (float)point.y;

	if (GetCursorPos( &point))
	{

		ScreenToClient(*this->hwndP, &point);
		mouseX = (float)point.x;
		mouseY = (float)point.y;

		//if (ScreenToClient(*this->hwndP, &point))
		//{
		///*if (mouseX > WIN_WIDTH)
		//	{
		//		point.x = (LONG)WIN_WIDTH;
		//		ScreenToClient(*this->hwndP, &point);
		//		SetCursorPos(point.x, point.y);
		//	}
		//if (mouseY > WIN_HEIGHT)
		//	{
		//		point.y = (LONG)WIN_HEIGHT;
		//		ScreenToClient(*this->hwndP, &point);
		//		SetCursorPos(point.x, point.y);
		//	}

		//if (mouseX < 0)
		//{
		//	point.x = 0;
		//	ScreenToClient(*this->hwndP, &point);
		//	SetCursorPos(point.x, point.y);
		//}
		//if (mouseY < 0)
		//{
		//	point.y = 0;
		//	ScreenToClient(*this->hwndP, &point);
		//	SetCursorPos(point.x, point.y);
		//}*/
		//}
		
	}
	/*else

	*/

	return XMFLOAT2(mouseX, mouseY);
}

bool InputHandler::isMouseClicked(InputKeys* mouseKey)
{
	mouse->GetDeviceState(sizeof(DIMOUSESTATE),(LPVOID)&mouseState);

	if (*mouseKey == MOUSE_LEFT && mouseState.rgbButtons[0] & 0x80)
	{
	return true;
	}

	if (*mouseKey == MOUSE_RIGHT && mouseState.rgbButtons[1] & 0x80)
	{
		return true;
	}

	return false;
}

void InputHandler::SetMouseVisibility(bool x)
{

	if (x == true)
	{
		//ShowCursor(TRUE);

		//SetCursor(LoadCursor(NULL, IDC_CROSS));
	}
	else
	{

		while (ShowCursor(FALSE) > 0);
	}

}

InputHandler * InputHandler::GetInstance()
{
	static InputHandler instance;
	return &instance;
}
