#include "MenuState.h"



MenuState::MenuState()
{
	mainUI = new GUI();
}


MenuState::~MenuState()
{
	delete mainUI;
}

void MenuState::Initialize()
{
	input = Input::GetInstance();
	exitMenu = false;
	mainUI->Initialize();

	mainUI->setUI(UITextures::MENU);


}

void MenuState::Release()
{
	mainUI->Release();
}

void MenuState::Update(double deltaTime)
{

	mainUI->Update(deltaTime);
	XMFLOAT2 mousePos = InputHandler::GetInstance()->GetMousePosition();

	float vx = ((2.0f * mousePos.x) / (float)WIN_HEIGHT - 1.0f);
	float vy = ((2.0f * -mousePos.y) / (float)WIN_WIDTH + 1.0f);
	
	if (vx > Maxex && vy < Maxey && vx < Minex && vy > Miney)
	{
		{
			if (input->isMouseClicked(MOUSE_LEFT))
			{
				//fix later

			}
			ProcessInput(&deltaTime);
		}
		
		//OnExit();
		//shutofgame, release everything no memory leaks are allowed
	}
	else if (vx > Maxnx && vy < Maxny && vx < Minnx && vy > Minny)
	{
		

		if (input->isMouseClicked(MOUSE_LEFT))
		{
			//OnExit();

			exitMenu = true;
		}
		
		//OnExit();
	}
	else if (vx > Maxcx && vy < Maxcy && vx < Mincx && vy > Mincy)
	{
		if (input->isMouseClicked(MOUSE_LEFT))
		{
			mainUI->setUI(UITextures::CONTROLS);

		}
		//go to control screen
	}

	if (mainUI->getUI() == UITextures::CONTROLS)
	{
		if (vx > MaxEcx && vy < MaxEcy && vx < MinEcx && vy > MinEcy)
		{
			if (input->isMouseClicked(MOUSE_LEFT))
			{
				mainUI->setUI(UITextures::MENU);
			}
		}
	}

		

	ProcessInput(&deltaTime);
	
}

void MenuState::ProcessInput(double * deltatime)
{
	
}

void MenuState::Render()
{
	mainUI->Render();
}

void MenuState::OnEnter()
{

}

void MenuState::OnExit()
{
	exitMenu = true;
}
