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

	//XMFLOAT2 Maxexit = { 47.0f ,391.0f };
	//XMFLOAT2 Minexit = { 245.0f,456.0f };

	//float Maxex = ((2.0f * Maxexit.x) / (float)WIN_HEIGHT - 1.0f);
	//float Maxey = ((2.0f * -Maxexit.y) / (float)WIN_WIDTH + 1.0f);
	//float Minex = ((2.0f * Minexit.x) / (float)WIN_HEIGHT - 1.0f);
	//float Miney = ((2.0f * -Minexit.y) / (float)WIN_WIDTH + 1.0f);

	XMFLOAT2 MaxNewGame = { 1025.0f,459.0f };
	XMFLOAT2 MinNewGame = { 1256.0f,545.0f };
	float Maxnx = ((2.0f * MaxNewGame.x) / (float)WIN_HEIGHT - 1.0f);
	float Maxny = ((2.0f * -MaxNewGame.y) / (float)WIN_WIDTH + 1.0f);
	float Minnx = ((2.0f * MinNewGame.x) / (float)WIN_HEIGHT - 1.0f);
	float Minny = ((2.0f * -MinNewGame.y) / (float)WIN_WIDTH + 1.0f);


	XMFLOAT2 MaxMenu = { 1025.0f,590.0f };
	XMFLOAT2 MinMenu = { 1256.0f,681.0f };
	float Maxmx = ((2.0f * MaxMenu.x) / (float)WIN_HEIGHT - 1.0f);
	float Maxmy = ((2.0f * -MaxMenu.y) / (float)WIN_WIDTH + 1.0f);
	float Minmx = ((2.0f * MinMenu.x) / (float)WIN_HEIGHT - 1.0f);
	float Minmy = ((2.0f * -MinMenu.y) / (float)WIN_WIDTH + 1.0f);

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
