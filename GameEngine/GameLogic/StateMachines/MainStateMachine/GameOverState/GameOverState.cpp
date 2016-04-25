#include "GameOverState.h"



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
	//game over screen msg YOU DIED, HIGHSCORE, RESTART OPTION, TIMER, EXIT GAME OPTION, GO TO MENU OPTION
	/*MessageBox(0, L"You Died",
	L"Continue", MB_OK);*/
	
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

void GameOverState::OnEnter()
{

}

void GameOverState::OnExit()
{

}
