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

void Engine::Initialize(HWND* window)
{
	input->Initialize();
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
