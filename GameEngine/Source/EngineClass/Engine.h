#pragma once

#pragma region Includes

#include "Graphics.h"
#include "InputHandler.h"
#include <windows.h>


#pragma endregion


class Engine
{


private:
	InputHandler* input;
	Graphics* graphics;

public:
	Engine();
	~Engine();
	void Initialize(HWND* window);
	void Release();

	void Frame(double* deltaTime);
	
	void Update();
	void Render();


};

 