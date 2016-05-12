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
	//mainUI->setUI(UITextures::MENU);
	XMFLOAT2 mousePos = InputHandler::GetInstance()->GetMousePosition();

	float vx = ((2.0f * mousePos.x) / (float)WIN_HEIGHT - 1.0f);
	float vy = ((2.0f * -mousePos.y) / (float)WIN_WIDTH + 1.0f);
	//Exit the game
	XMFLOAT2 Maxexit = { 50.0f ,597.0f };
	XMFLOAT2 Minexit = { 246.0f,672.0f };

	float Maxex = ((2.0f * Maxexit.x) / (float)WIN_HEIGHT - 1.0f);
	float Maxey = ((2.0f * -Maxexit.y) / (float)WIN_WIDTH + 1.0f);
	float Minex = ((2.0f * Minexit.x) / (float)WIN_HEIGHT - 1.0f);
	float Miney = ((2.0f * -Minexit.y) / (float)WIN_WIDTH + 1.0f);
	//NewGame
	XMFLOAT2 MaxNewGame = {50.0f,373.0f};
	XMFLOAT2 MinNewGame = {246.0f,446.0f};
	float Maxnx = ((2.0f * MaxNewGame.x) / (float)WIN_HEIGHT - 1.0f);
	float Maxny = ((2.0f * -MaxNewGame.y) / (float)WIN_WIDTH + 1.0f);
	float Minnx = ((2.0f * MinNewGame.x) / (float)WIN_HEIGHT - 1.0f);
	float Minny = ((2.0f * -MinNewGame.y) / (float)WIN_WIDTH + 1.0f);
	//Show the control UI 
	XMFLOAT2 MaxControls = { 50.0f,486.0f };
	XMFLOAT2 MinControls = {246.0f,672.0f};
	float Maxcx = ((2.0f * MaxControls.x) / (float)WIN_HEIGHT - 1.0f);
	float Maxcy = ((2.0f * -MaxControls.y) / (float)WIN_WIDTH + 1.0f);
	float Mincx = ((2.0f * MinControls.x) / (float)WIN_HEIGHT - 1.0f);
	float Mincy = ((2.0f * -MinControls.y) / (float)WIN_WIDTH + 1.0f);

	XMFLOAT2 ExitControlMAX = {101.0f,581.0f};
	XMFLOAT2 ExitControlMIN = {168.0f,619.0f};
	float MaxEcx = ((2.0f * ExitControlMAX.x) / (float)WIN_HEIGHT - 1.0f);
	float MaxEcy = ((2.0f * -ExitControlMAX.y) / (float)WIN_WIDTH + 1.0f);
	float MinEcx = ((2.0f * ExitControlMIN.x) / (float)WIN_HEIGHT - 1.0f);
	float MinEcy = ((2.0f * -ExitControlMIN.y) / (float)WIN_WIDTH + 1.0f);
	//XMVECTOR rayOrigin = XMVectorSet(vx, vy, 0.0f, 1.0f);
	//XMVECTOR rayDir = rayOrigin;
	if (vx > Maxex && vy < Maxey && vx < Minex && vy > Miney)
	{
		{
			if (input->isMouseClicked(MOUSE_LEFT))
			{
			
			}
			ProcessInput(&deltaTime);
		}
		
		//shutofgame, release everything no memory leaks are allowed
		//OnExit();
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
		}
		//go to control screen
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
