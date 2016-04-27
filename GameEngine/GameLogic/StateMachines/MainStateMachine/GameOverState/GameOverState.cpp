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

	std::wstring a = std::to_wstring( (int)this->GetPoints());

	

	/*std::wstring stemp = s2ws(a);*/
	
	

	LPCWSTR result = a.c_str();

	MessageBox(0, result ,
	L"Score", MB_OK);
	
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

void GameOverState::OnEnter()
{

}

void GameOverState::OnExit()
{

}
