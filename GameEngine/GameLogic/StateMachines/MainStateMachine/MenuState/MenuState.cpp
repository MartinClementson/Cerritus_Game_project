#include "MenuState.h"



MenuState::MenuState()
{
}


MenuState::~MenuState()
{
}

void MenuState::Initialize()
{
	input = Input::GetInstance();
	exitMenu = false;
}

void MenuState::Release()
{
}

void MenuState::Update(double deltaTime)
{
	ProcessInput(&deltaTime);
}

void MenuState::ProcessInput(double * deltatime)
{
	if (input->IsKeyPressed(KEY_W))
	{
		exitMenu = true;
		/*MessageBox(0, L"Main Menu",
			L"Continue", MB_OK);*/
	}
}

void MenuState::Render()
{
}

void MenuState::OnEnter()
{
}

void MenuState::OnExit()
{
}
