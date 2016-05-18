#include "WinState.h"
#include <string>
//#include <string.h>



WinState::WinState()
{
	WinUI = new GUI();
}


WinState::~WinState()
{
	delete WinUI;
}

void WinState::Initialize()
{
	input = Input::GetInstance();
	replay = false;
	toMenu = false;
	WinUI->Initialize();
	WinUI->setUI(UITextures::WIN);
}

void WinState::Release()
{
	WinUI->Release();
}

void WinState::Update(double deltaTime)
{

	WinUI->Update(deltaTime);

	XMFLOAT2 mousePos = InputHandler::GetInstance()->GetMousePosition();

	float vx = ((2.0f * mousePos.x) / (float)WIN_HEIGHT - 1.0f);
	float vy = ((2.0f * -mousePos.y) / (float)WIN_WIDTH + 1.0f);


	if (vx > Maxmx && vy < Maxmy && vx < Minmx && vy > Minmy)
	{
		if (input->isMouseClicked(MOUSE_LEFT))
		{
			toMenu = true;
		}

		//OnExit();
	}
	else if (vx > Maxnx && vy < Maxny && vx < Minnx && vy > Minny)
	{
		if (input->isMouseClicked(MOUSE_LEFT))
		{
			OnExit();
		}
	}

	//replay = true;

	ProcessInput(&deltaTime);
}

void WinState::Render()
{
	WinUI->Render();
}

void WinState::ProcessInput(double * deltaTime)
{


	//if (input->IsKeyPressed(KEY_SPACE))
	//{
	//	replay = true;
	//	/*MessageBox(0, L"ENTER",
	//	L"Continue", MB_OK);*/
	//	//timeSincePaused = 0.0f;
	//}

}

void WinState::SetPoints(float points)
{
	this->points = points;
}

float WinState::GetPoints()
{
	return this->points;
}

void WinState::SetLastHigh(float high)
{
	this->lastHighscore = high;
}

void WinState::OnEnter()
{
	replay = false;
}

void WinState::OnExit()
{
	replay = true;
}
