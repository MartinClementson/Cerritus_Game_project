#include "GameOverState.h"
#include <string>
//#include <string.h>



GameOverState::GameOverState()
{
	gameOverGUI = new GUI();
}


GameOverState::~GameOverState()
{
	delete gameOverGUI;
}

void GameOverState::Initialize()
{
	input = Input::GetInstance();
	replay = false;
	toMenu = false;
	gameOverGUI->Initialize();
	gameOverGUI->setUI(UITextures::GAMEOVER);
}

void GameOverState::Release()
{
	gameOverGUI->Release();
}

void GameOverState::Update(double deltaTime)
{
	//game over screen msg YOU DIED, HIGHSCORE, RESTART OPTION,
	//TIMER, EXIT GAME OPTION, GO TO MENU OPTION
	gameOverGUI->Update(deltaTime);
	
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

void GameOverState::Render()
{
	gameOverGUI->Render();
}

void GameOverState::ProcessInput(double * deltaTime)
{


	//if (input->IsKeyPressed(KEY_SPACE))
	//{
	//	replay = true;
	//	/*MessageBox(0, L"ENTER",
	//	L"Continue", MB_OK);*/
	//	//timeSincePaused = 0.0f;
	//}

}

void GameOverState::SetPoints(float points)
{
	this->points = points;
}

float GameOverState::GetPoints()
{
	return this->points;
}

void GameOverState::SetLastHigh(float high)
{
	this->lastHighscore = high;
}

void GameOverState::OnEnter()
{
	replay = false;
}

void GameOverState::OnExit()
{
	replay = true;
}
