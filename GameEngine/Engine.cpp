#include "Engine.h"



Engine::Engine()
{
	this->input = new InputHandler();
	this->graphics = new Graphics();
}


Engine::~Engine()
{
	delete this->graphics;
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
