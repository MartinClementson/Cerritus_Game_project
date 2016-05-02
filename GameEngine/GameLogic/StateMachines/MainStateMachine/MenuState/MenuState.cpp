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
	
	ProcessInput(&deltaTime);
	
}

void MenuState::ProcessInput(double * deltatime)
{
	
	InputHandler::GetInstance()->GetMousePosition();
	
	if (input->IsKeyPressed(KEY_W))
	{
		OnExit();
		/*MessageBox(0, L"Main Menu",
			L"Continue", MB_OK);*/
	}
	XMFLOAT2 mousePos;

	float vx = ((2.0f * mousePos.x) / (float)WIN_HEIGHT - 1.0f);
	float vy = ((2.0f * -mousePos.y) / (float)WIN_WIDTH + 1.0f);

	XMVECTOR rayOrigin = XMVectorSet(vx, vy, 0.0f, 1.0f);
	XMVECTOR rayDir = rayOrigin;

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
