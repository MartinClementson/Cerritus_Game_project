#include "Engine.h"



Engine::Engine()
{
	this->input = InputHandler::GetInstance();
	this->graphics = Graphics::GetInstance();
	this->game = new Game();
}


Engine::~Engine()
{
	delete this->game;
}

void Engine::Initialize(HWND* window, HINSTANCE hInstance)
{
	if (!input->Initialize(window,hInstance))
	{
		MessageBox(0, L"DIRECT INPUT INITILIZATION - FAILED",
			L"ERROR", MB_OK);
	}
	input->Initialize(window, hInstance);
	graphics->Initialize(window);
	game->Initialize();

}

void Engine::Release()
{
	graphics->Release();
	input->Release();
	game->Release();
}

void Engine::Frame(double * deltaTime)
{
	Render();
}

void Engine::Update(double* deltaTime)
{
	game->Update(deltaTime[0]);
}

void Engine::Render()
{
	graphics->Render();
	game->Render();
}
