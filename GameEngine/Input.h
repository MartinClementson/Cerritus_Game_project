#pragma once
#include "InputHandler.h"

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
	/*bool IsKeyPressed(InputKeys* key);
	bool IsKeyHeld(InputKeys* key);
	XMVECTOR2 GetMousePosition();
	bool isMouseClicked(InputKeys* mouseKey);*/

};

