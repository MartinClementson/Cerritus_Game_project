#include "Game.h"



Game::Game()
{
	this->stateMachine = new MainStateMachine();
}

Game::~Game()
{
	delete this->stateMachine;
}

void Game::Initialize()
{
	stateMachine->Initialize();
}

void Game::Release()
{
	stateMachine->Release();
}

void Game::Update(double deltaTime)
{
	stateMachine->Update(deltaTime);
}

void Game::Render()
{
	stateMachine->Render();
}
