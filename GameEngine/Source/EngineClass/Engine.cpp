#include "Engine.h"



Engine::Engine()
{
	this->input = InputHandler::GetInstance();
	this->graphics = Graphics::GetInstance();
}


Engine::~Engine()
{

}

void Engine::Initialize(HWND* window)
{
	input->Initialize();
	graphics->Initialize(window);

}

void Engine::Release()
{
	graphics->Release();
	input->Release();
}

void Engine::Frame(double * deltaTime)
{
	Render();
}

void Engine::Update()
{
}

void Engine::Render()
{
	graphics->Render();
}
