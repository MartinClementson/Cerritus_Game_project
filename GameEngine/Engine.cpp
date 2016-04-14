#include "Engine.h"



Engine::Engine()
{
	this->graphics = new Graphics();
}


Engine::~Engine()
{
	delete this->graphics;
}

void Engine::Initialize(HWND* window)
{
	graphics->Initialize(window);

}

void Engine::Release()
{
	graphics->Release();
}

void Engine::Frame(double * deltaTime)
{
}

void Engine::Update()
{
}

void Engine::Render()
{
}
