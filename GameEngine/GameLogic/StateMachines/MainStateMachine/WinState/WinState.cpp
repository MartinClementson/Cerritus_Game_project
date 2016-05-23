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
	graphics = Graphics::GetInstance();
	replay = false;
	toMenu = false;
	WinUI->Initialize();

	win.UIobject = UITextures::WIN;
	win2.UIobject = UITextures::HSLEFT;
	win3.UIobject = UITextures::HSMIDDLE;
	win4.UIobject = UITextures::HSRIGHT;

	win5.UIobject = UITextures::SLEFT;
	win6.UIobject = UITextures::SMIDDLE;
	win7.UIobject = UITextures::SRIGHT;

	this->number  = 0;
	this->number1 = 0;
	this->number2 = 0;
	this->number3 = 0;

	this->highNumber1 = 0;
	this->highNumber2 = 0;
	this->highNumber3 = 0;
}

void WinState::Release()
{
	WinUI->Release();
}

void WinState::Update(double deltaTime)
{

	WinUI->Update(deltaTime);
	SetPointPlacing();

	QuadNumberPick((int)number1);
	QuadNumberPick1((int)number2);
	QuadNumberPick2((int)number3);

	SetHighPlacing();

	QuadNumberPickScore((int)highNumber1);
	QuadNumberPickScore1((int)highNumber2);
	QuadNumberPickScore2((int)highNumber3);

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
}

void WinState::Render()
{
	//WinUI->Render();

	graphics->QueueRender(&win);

	graphics->QueueRender(&win2);
	graphics->QueueRender(&win3);
	graphics->QueueRender(&win4);

	graphics->QueueRender(&win5);
	graphics->QueueRender(&win6);
	graphics->QueueRender(&win7);
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
float WinState::GetLastHigh()
{
	return lastHighscore;
}

void WinState::SetPointPlacing()
{
	float points1 = 0;
	points1 = GetPoints();
	number = points1;

	number1 = 0;
	number1 = number / 100;
	number1 = (float)((int)number1);

	float minusNum = 0;
	minusNum = 100 * number1;

	number2 = points1;
	number2 = number2 - minusNum;
	number2 = number2 / 10;
	number2 = (float)((int)number2);

	float minusNum2 = 0;
	minusNum2 = 10 * number2;

	number3 = points1 - minusNum - minusNum2;
	number3 = (float)((int)number3);
}

int WinState::GetNumber1()
{
	return (int)number1;
}

int WinState::GetNumber2()
{
	return (int)number2;
}

int WinState::GetNumber3()
{
	return (int)number3;
}

void WinState::QuadNumberPick(int cases)
{

	switch (cases)
	{
	case 0:
		win2.UInumber = UiNumbers::ZERO;
		break;

	case 1:
		win2.UInumber = UiNumbers::ONE;
		break;

	case 2:
		win2.UInumber = UiNumbers::TWO;
		break;

	case 3:
		win2.UInumber = UiNumbers::THREE;
		break;

	case 4:
		win2.UInumber = UiNumbers::FOUR;
		break;

	case 5:
		win2.UInumber = UiNumbers::FIVE;
		break;
	case 6:
		win2.UInumber = UiNumbers::SIX;
		break;

	case 7:
		win2.UInumber = UiNumbers::SEVEN;
		break;

	case 8:
		win2.UInumber = UiNumbers::EIGHT;
		break;

	case 9:
		win2.UInumber = UiNumbers::NINE;
		break;
	}
}

void WinState::QuadNumberPick1(int cases)
{

	switch (cases)
	{
	case 0:
		win3.UInumber = UiNumbers::ZERO;
		break;

	case 1:
		win3.UInumber = UiNumbers::ONE;
		break;

	case 2:
		win3.UInumber = UiNumbers::TWO;
		break;

	case 3:
		win3.UInumber = UiNumbers::THREE;
		break;

	case 4:
		win3.UInumber = UiNumbers::FOUR;
		break;

	case 5:
		win3.UInumber = UiNumbers::FIVE;
		break;
	case 6:
		win3.UInumber = UiNumbers::SIX;
		break;

	case 7:
		win3.UInumber = UiNumbers::SEVEN;
		break;

	case 8:
		win3.UInumber = UiNumbers::EIGHT;
		break;

	case 9:
		win3.UInumber = UiNumbers::NINE;
		break;
	}
}

void WinState::QuadNumberPick2(int cases)
{

	switch (cases)
	{
	case 0:
		win4.UInumber = UiNumbers::ZERO;
		break;

	case 1:
		win4.UInumber = UiNumbers::ONE;
		break;

	case 2:
		win4.UInumber = UiNumbers::TWO;
		break;

	case 3:
		win4.UInumber = UiNumbers::THREE;
		break;

	case 4:
		win4.UInumber = UiNumbers::FOUR;
		break;

	case 5:
		win4.UInumber = UiNumbers::FIVE;
		break;
	case 6:
		win4.UInumber = UiNumbers::SIX;
		break;

	case 7:
		win4.UInumber = UiNumbers::SEVEN;
		break;

	case 8:
		win4.UInumber = UiNumbers::EIGHT;
		break;

	case 9:
		win4.UInumber = UiNumbers::NINE;
		break;
	}
}

void WinState::SetHighPlacing()
{
	float points1 = 0;
	points1 = GetLastHigh();
	highNumber = points1;

	highNumber1 = 0;
	highNumber1 = highNumber / 100;
	highNumber1 = (float)((int)highNumber1);

	float minusNum = 0;
	minusNum = 100 * highNumber1;

	highNumber2 = points1;
	highNumber2 = highNumber2 - minusNum;
	highNumber2 = highNumber2 / 10;
	highNumber2 = (float)((int)highNumber2);

	float minusNum2 = 0;
	minusNum2 = 10 * highNumber2;

	highNumber3 = points1 - minusNum - minusNum2;
	highNumber3 = (float)((int)highNumber3);


	SetLastHighScoreNumbers((int)highNumber1, (int)highNumber2, (int)highNumber3);
}

void WinState::SetLastHighScoreNumbers(int HN1, int HN2, int HN3)
{
	this->highNumber1 = (float)HN1;
	this->highNumber2 = (float)HN2;
	this->highNumber3 = (float)HN3;
}

int WinState::GetScoreNumber1()
{
	return (int)highNumber1;
}

int WinState::GetScoreNumber2()
{
	return (int)highNumber2;
}

int WinState::GetScoreNumber3()
{
	return (int)highNumber3;
}

void WinState::QuadNumberPickScore(int cases)
{

	switch (cases)
	{
	case 0:
		win5.UInumber = UiNumbers::ZERO;
		break;

	case 1:
		win5.UInumber = UiNumbers::ONE;
		break;

	case 2:
		win5.UInumber = UiNumbers::TWO;
		break;

	case 3:
		win5.UInumber = UiNumbers::THREE;
		break;

	case 4:
		win5.UInumber = UiNumbers::FOUR;
		break;

	case 5:
		win5.UInumber = UiNumbers::FIVE;
		break;
	case 6:
		win5.UInumber = UiNumbers::SIX;
		break;

	case 7:
		win5.UInumber = UiNumbers::SEVEN;
		break;

	case 8:
		win5.UInumber = UiNumbers::EIGHT;
		break;

	case 9:
		win5.UInumber = UiNumbers::NINE;
		break;
	}
}

void WinState::QuadNumberPickScore1(int cases)
{

	switch (cases)
	{
	case 0:
		win6.UInumber = UiNumbers::ZERO;
		break;

	case 1:
		win6.UInumber = UiNumbers::ONE;
		break;

	case 2:
		win6.UInumber = UiNumbers::TWO;
		break;

	case 3:
		win6.UInumber = UiNumbers::THREE;
		break;

	case 4:
		win6.UInumber = UiNumbers::FOUR;
		break;

	case 5:
		win6.UInumber = UiNumbers::FIVE;
		break;
	case 6:
		win6.UInumber = UiNumbers::SIX;
		break;

	case 7:
		win6.UInumber = UiNumbers::SEVEN;
		break;

	case 8:
		win6.UInumber = UiNumbers::EIGHT;
		break;

	case 9:
		win6.UInumber = UiNumbers::NINE;
		break;
	}
}

void WinState::QuadNumberPickScore2(int cases)
{

	switch (cases)
	{
	case 0:
		win7.UInumber = UiNumbers::ZERO;
		break;

	case 1:
		win7.UInumber = UiNumbers::ONE;
		break;

	case 2:
		win7.UInumber = UiNumbers::TWO;
		break;

	case 3:
		win7.UInumber = UiNumbers::THREE;
		break;

	case 4:
		win7.UInumber = UiNumbers::FOUR;
		break;

	case 5:
		win7.UInumber = UiNumbers::FIVE;
		break;
	case 6:
		win7.UInumber = UiNumbers::SIX;
		break;

	case 7:
		win7.UInumber = UiNumbers::SEVEN;
		break;

	case 8:
		win7.UInumber = UiNumbers::EIGHT;
		break;

	case 9:
		win7.UInumber = UiNumbers::NINE;
		break;
	}
}

void WinState::OnEnter()
{
	replay = false;
}

void WinState::OnExit()
{
	replay = true;
}
