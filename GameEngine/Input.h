#pragma once
#include "InputHandler.h"
#include "LibIncluder.h"

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
	//bool IsKeyPressed(InputKeys* key;//need enums
	//bool IsKeyHeld(InputKeys* key);//need enums
	DirectX::XMFLOAT2 GetMousePosition();
	//bool isMouseClicked(InputKeys* mouseKey);//need enums

};

