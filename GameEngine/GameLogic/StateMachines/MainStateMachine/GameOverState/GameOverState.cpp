#include "GameOverState.h"
#include <string>
//#include <string.h>



GameOverState::GameOverState()
{

}


GameOverState::~GameOverState()
{
}

void GameOverState::Initialize()
{
	input = Input::GetInstance();
	replay = false;
}

void GameOverState::Release()
{

}

void GameOverState::Update(double deltaTime)
{
	//game over screen msg YOU DIED, HIGHSCORE, RESTART OPTION,
	//TIMER, EXIT GAME OPTION, GO TO MENU OPTION

	

	

	/*std::wstring stemp = s2ws(a);*/
	
	

	
	if (this->GetPoints() > lastHighscore)
	{
		std::wstring a = std::to_wstring((int)this->GetPoints());
		LPCWSTR result = a.c_str();
		MessageBox(0, result,
			L"New Highscore!", MB_OK);
	}
	else if (this->GetPoints() == lastHighscore && lastHighscore == 0)
	{
		std::wstring a = std::to_wstring((int)this->GetPoints());
		LPCWSTR result = a.c_str();
		MessageBox(0, result,
			L"You Can Do Better Than That...", MB_OK);
	}
	else if (this->GetPoints() == lastHighscore)
	{
		std::wstring a = std::to_wstring((int)this->GetPoints());
		LPCWSTR result = a.c_str();
		MessageBox(0, result,
			L"Equaled The Best", MB_OK);
	}
	else if (this->GetPoints() < lastHighscore && lastHighscore == 0)
	{
		std::wstring a = std::to_wstring((int)this->GetPoints());
		LPCWSTR result = a.c_str();
		MessageBox(0, result,
			L"You Aren't Even Trying", MB_OK);
	}
	else
	{
		
		LPCWSTR tmp = L"last Highscore: ";

		std::wstring a = std::to_wstring((int)this->GetPoints());
		LPCWSTR result = a.c_str();
		wstring prev(tmp);
		prev = prev + std::to_wstring((int)lastHighscore);
		LPCWSTR print = prev.c_str();
		
		MessageBox(0, result,
			print, MB_OK);
	}
	

	replay = true;
	
	ProcessInput(&deltaTime);
}

void GameOverState::Render()
{

}

void GameOverState::ProcessInput(double * deltaTime)
{


	if (input->IsKeyPressed(KEY_SPACE))
	{
		replay = true;
		/*MessageBox(0, L"ENTER",
		L"Continue", MB_OK);*/
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

void GameOverState::SetLastHigh(float high)
{
	this->lastHighscore = high;
}

void GameOverState::OnEnter()
{

}

void GameOverState::OnExit()
{

}
