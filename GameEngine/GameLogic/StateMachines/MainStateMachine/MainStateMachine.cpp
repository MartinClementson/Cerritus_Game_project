#include "MainStateMachine.h"



MainStateMachine::MainStateMachine()
{
}


MainStateMachine::~MainStateMachine()
{
}

void MainStateMachine::Update(double deltaTime)
{
	if (gameState->isActive)
	{
		gameState->Update(deltaTime);
	}
	else if (gameOverState->isActive)
	{
		gameOverState->Update(deltaTime);
	}
	else if (menuState->isActive)
	{
		menuState->Update(deltaTime);
	}
}

void MainStateMachine::Render()
{
	if(gameState->isActive)
	{
		gameState->Render();
	}
	else if (gameOverState->isActive)
	{
		gameOverState->Render();
	}
	else if (menuState->isActive)
	{
		menuState->Render();
	}
}

void MainStateMachine::Initialize()
{
}

void MainStateMachine::Release()
{
}
