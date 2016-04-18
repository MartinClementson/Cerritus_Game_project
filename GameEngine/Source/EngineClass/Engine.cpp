#include "Engine.h"



Engine::Engine()
{
	this->input = new InputHandler();
	this->graphics = Graphics::GetInstance();
}


Engine::~Engine()
{

	delete this->input;
}

void Engine::Initialize(HWND* window)
{
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
