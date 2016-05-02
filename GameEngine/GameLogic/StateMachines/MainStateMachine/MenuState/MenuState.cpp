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

	XMFLOAT2 exit = { 1.250f,4.598f };

	float ex = ((2.0f * exit.x) / (float)WIN_HEIGHT - 1.0f);
	float ey = ((2.0f * -exit.y) / (float)WIN_WIDTH + 1.0f);
	
	XMFLOAT2 newGame = {1.250f,2.736f};

	float nx = ((2.0f*newGame.x) / (float)WIN_HEIGHT - 1.0f);
	float ny = ((2.0f*-newGame.y) / (float)WIN_WIDTH + 1.0f);
	
	XMFLOAT2 controls = { 1.250f,3.778f };

	float cx = ((2.0f*controls.x)/(float)WIN_HEIGHT - 1.0f);
	float cy = ((2.0f*-controls.y)/(float)WIN_WIDTH + 1.0f); 
	
	//XMVECTOR rayOrigin = XMVectorSet(vx, vy, 0.0f, 1.0f);
	//XMVECTOR rayDir = rayOrigin;
	
	
	// i think this is the exit position 
	
	if (vx == ex && vy == ey)
	{
		OnExit();
	}
	//{
	//	//New Game
	//}
	//else if (InputHandler::GetInstance()->GetMousePosition().y == 4.494f)
	//{
	//	//controls
	//}
	//else if (InputHandler::GetInstance()->GetMousePosition().y == 4.598f)
	//{
	//	OnExit();
	//}

		

	ProcessInput(&deltaTime);
	
}

void MenuState::ProcessInput(double * deltatime)
{
	
	
	
	if (input->IsKeyPressed(KEY_W))
	{
		OnExit();
		/*MessageBox(0, L"Main Menu",
			L"Continue", MB_OK);*/
	}
	

	

	/*Step one, create a grid and update it for every object that moves.
	Only check for collisions between objects in the same squares.
	Check if the bounding box of the objects intersects (their containing rectangle).
	Check for pixel perfect collision using a low res version of the outline(see Game Physics).
	Do a normal check of the outline tracing as described in Game Physics (Q 2)*/
	//kolla vilken knapp som blir klickad på i menyn. 
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
