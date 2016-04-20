#include "Input.h"




Input::Input()
{
}


Input::~Input()
{
}

void Input::Initialize()
{
	inputHandling = InputHandler::GetInstance();
}

void Input::Release()
{
}

bool Input::IsKeyPressed(InputKeys key)
{
	return inputHandling->IsKeyPressed(&key);
}

bool Input::IsKeyHeld(InputKeys key)
{
	return inputHandling->IsKeyHeld(&key);
}

XMFLOAT2 Input::GetMousePosition()
{
	return inputHandling->GetMousePosition();
}

bool Input::isMouseClicked(InputKeys mouseKey)
{
	return inputHandling->isMouseClicked(&mouseKey);
}

Input* Input::GetInstance()
{
	static Input instance;
	return &instance;
}
