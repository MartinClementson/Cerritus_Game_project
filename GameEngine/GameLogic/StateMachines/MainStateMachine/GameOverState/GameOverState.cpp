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
	graphics = Graphics::GetInstance();
	replay = false;
	toMenu = false;
	gameOverGUI->Initialize();
	gameover.UIobject = UITextures::GAMEOVER;
	gameover2.UIobject = UITextures::HSLEFT;
	gameover3.UIobject = UITextures::HSMIDDLE;
	gameover4.UIobject = UITextures::HSRIGHT;

	gameover5.UIobject = UITextures::SLEFT;
	gameover6.UIobject = UITextures::SMIDDLE;
	gameover7.UIobject = UITextures::SRIGHT;

	float number = 0;
	float number1 = 0;
	float number2 = 0;
	float number3 = 0;

	float highNumber1 = 0;
	float highNumber2 = 0;
	float highNumber3 = 0;
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
	SetPointPlacing();

	QuadNumberPick(number1);
	QuadNumberPick1(number2);
	QuadNumberPick2(number3);

	SetHighPlacing();

	QuadNumberPickScore(highNumber1);
	QuadNumberPickScore1(highNumber2);
	QuadNumberPickScore2(highNumber3);
	
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
	graphics->QueueRender(&gameover);

	graphics->QueueRender(&gameover2);
	graphics->QueueRender(&gameover3);
	graphics->QueueRender(&gameover4);

	graphics->QueueRender(&gameover5);
	graphics->QueueRender(&gameover6);
	graphics->QueueRender(&gameover7);

}

void GameOverState::ProcessInput(double * deltaTime)
{
	if (input->IsKeyPressed(KEY_SPACE))
	{
		//replay = true;
		///*MessageBox(0, L"ENTER",
		//L"Continue", MB_OK);*/
		//timeSincePaused = 0.0f;
	}
}

void GameOverState::SetPoints(float points)
{
	this->points = points;
}

float GameOverState::GetPoints()
{
	return this->points;
}

void GameOverState::OnEnter()
{
	replay = false;
}

void GameOverState::OnExit()
{
	replay = true;
}

void GameOverState::SetPointPlacing()
{
	float points = GetPoints();
	number = points;

	number1 = 0;
	number1 = number / 100;
	number1 = (int)number1;

	float minusNum = 0;
	minusNum = 100 * number1;

	number2 = points;
	number2 = number2 - minusNum;
	number2 = number2 / 10;
	number2 = (int)number2;

	float minusNum2 = 0;
	minusNum2 = 10 * number2;
	
	number3 = points - minusNum - minusNum2;
	number3 = (int)number3;
}

int GameOverState::GetNumber1()
{
	return number1;
}

int GameOverState::GetNumber2()
{
	return number2;
}

int GameOverState::GetNumber3()
{
	return number3;
}

void GameOverState::QuadNumberPick(int cases)
{

	switch (cases)
	{
	case 0:
		gameover2.UInumber = UiNumbers::ZERO;
		break;

	case 1:
		gameover2.UInumber = UiNumbers::ONE;
		break;

	case 2:
		gameover2.UInumber = UiNumbers::TWO;
		break;

	case 3:
		gameover2.UInumber = UiNumbers::THREE;
		break;

	case 4:
		gameover2.UInumber = UiNumbers::FOUR;
		break;

	case 5:
		gameover2.UInumber = UiNumbers::FIVE;
		break;
	case 6:
		gameover2.UInumber = UiNumbers::SIX;
		break;

	case 7:
		gameover2.UInumber = UiNumbers::SEVEN;
		break;

	case 8:
		gameover2.UInumber = UiNumbers::EIGHT;
		break;

	case 9:
		gameover2.UInumber = UiNumbers::NINE;
		break;
	}
}


void GameOverState::QuadNumberPick1(int cases)
{

	switch (cases)
	{
	case 0:
		gameover3.UInumber = UiNumbers::ZERO;
		break;

	case 1:
		gameover3.UInumber = UiNumbers::ONE;
		break;

	case 2:
		gameover3.UInumber = UiNumbers::TWO;
		break;

	case 3:
		gameover3.UInumber = UiNumbers::THREE;
		break;

	case 4:
		gameover3.UInumber = UiNumbers::FOUR;
		break;

	case 5:
		gameover3.UInumber = UiNumbers::FIVE;
		break;
	case 6:
		gameover3.UInumber = UiNumbers::SIX;
		break;

	case 7:
		gameover3.UInumber = UiNumbers::SEVEN;
		break;

	case 8:
		gameover3.UInumber = UiNumbers::EIGHT;
		break;

	case 9:
		gameover3.UInumber = UiNumbers::NINE;
		break;
	}
}


void GameOverState::QuadNumberPick2(int cases)
{

	switch (cases)
	{
	case 0:
		gameover4.UInumber = UiNumbers::ZERO;
		break;

	case 1:
		gameover4.UInumber = UiNumbers::ONE;
		break;

	case 2:
		gameover4.UInumber = UiNumbers::TWO;
		break;

	case 3:
		gameover4.UInumber = UiNumbers::THREE;
		break;

	case 4:
		gameover4.UInumber = UiNumbers::FOUR;
		break;

	case 5:
		gameover4.UInumber = UiNumbers::FIVE;
		break;
	case 6:
		gameover4.UInumber = UiNumbers::SIX;
		break;

	case 7:
		gameover4.UInumber = UiNumbers::SEVEN;
		break;

	case 8:
		gameover4.UInumber = UiNumbers::EIGHT;
		break;

	case 9:
		gameover4.UInumber = UiNumbers::NINE;
		break;
	}
}

void GameOverState::SetLastHigh(float high)
{
	this->lastHighscore = high;
}

float GameOverState::GetLastHigh()
{
	return lastHighscore;
}

void GameOverState::SetHighPlacing()
{
	float points = GetLastHigh();
	highNumber = points;

	highNumber1 = 0;
	highNumber1 = highNumber / 100;
	highNumber1 = (int)highNumber;

	float minusNum = 0;
	minusNum = 100 * number1;

	highNumber2 = points;
	highNumber2 = highNumber2 - minusNum;
	highNumber2 = highNumber2 / 10;
	highNumber2 = (int)highNumber2;

	float minusNum2 = 0;
	minusNum2 = 10 * number2;

	highNumber3 = points - minusNum - minusNum2;
	highNumber3 = (int)highNumber3;
}

int GameOverState::GetScoreNumber1()
{
	return highNumber1;
}

int GameOverState::GetScoreNumber2()
{
	return highNumber2;
}

int GameOverState::GetScoreNumber3()
{
	return highNumber3;
}

void GameOverState::QuadNumberPickScore(int cases)
{

	switch (cases)
	{
	case 0:
		gameover5.UInumber = UiNumbers::ZERO;
		break;

	case 1:
		gameover5.UInumber = UiNumbers::ONE;
		break;

	case 2:
		gameover5.UInumber = UiNumbers::TWO;
		break;

	case 3:
		gameover5.UInumber = UiNumbers::THREE;
		break;

	case 4:
		gameover5.UInumber = UiNumbers::FOUR;
		break;

	case 5:
		gameover5.UInumber = UiNumbers::FIVE;
		break;
	case 6:
		gameover5.UInumber = UiNumbers::SIX;
		break;

	case 7:
		gameover5.UInumber = UiNumbers::SEVEN;
		break;

	case 8:
		gameover5.UInumber = UiNumbers::EIGHT;
		break;

	case 9:
		gameover5.UInumber = UiNumbers::NINE;
		break;
	}
}

void GameOverState::QuadNumberPickScore1(int cases)
{

	switch (cases)
	{
	case 0:
		gameover6.UInumber = UiNumbers::ZERO;
		break;

	case 1:
		gameover6.UInumber = UiNumbers::ONE;
		break;

	case 2:
		gameover6.UInumber = UiNumbers::TWO;
		break;

	case 3:
		gameover6.UInumber = UiNumbers::THREE;
		break;

	case 4:
		gameover6.UInumber = UiNumbers::FOUR;
		break;

	case 5:
		gameover6.UInumber = UiNumbers::FIVE;
		break;
	case 6:
		gameover6.UInumber = UiNumbers::SIX;
		break;

	case 7:
		gameover6.UInumber = UiNumbers::SEVEN;
		break;

	case 8:
		gameover6.UInumber = UiNumbers::EIGHT;
		break;

	case 9:
		gameover6.UInumber = UiNumbers::NINE;
		break;
	}
}

void GameOverState::QuadNumberPickScore2(int cases)
{

	switch (cases)
	{
	case 0:
		gameover7.UInumber = UiNumbers::ZERO;
		break;

	case 1:
		gameover7.UInumber = UiNumbers::ONE;
		break;

	case 2:
		gameover7.UInumber = UiNumbers::TWO;
		break;

	case 3:
		gameover7.UInumber = UiNumbers::THREE;
		break;

	case 4:
		gameover7.UInumber = UiNumbers::FOUR;
		break;

	case 5:
		gameover7.UInumber = UiNumbers::FIVE;
		break;
	case 6:
		gameover7.UInumber = UiNumbers::SIX;
		break;

	case 7:
		gameover7.UInumber = UiNumbers::SEVEN;
		break;

	case 8:
		gameover7.UInumber = UiNumbers::EIGHT;
		break;

	case 9:
		gameover7.UInumber = UiNumbers::NINE;
		break;
	}
}