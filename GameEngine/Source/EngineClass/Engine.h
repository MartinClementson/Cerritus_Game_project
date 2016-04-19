#pragma once

#pragma region Includes

#include "../../ResourceEngine/Graphics/Graphics.h"
#include "../../GameLogic/InputHandler/InputHandler.h"
#include <windows.h>
#include "../../GameLogic/Game.h"


#pragma endregion


class Engine
{


private:
	InputHandler* input;
	Graphics* graphics;
	Game* game;

public:
	Engine();
	~Engine();

	void Initialize(HWND* window,HINSTANCE *hInstance);

	void Release();

	void Frame(double* deltaTime);
	
	void Update(double* deltaTime);
	void Render();


};

 