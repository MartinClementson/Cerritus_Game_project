#pragma once
#include "../../StateClass/StateClass.h"
#include "../../../Scene/Scene.h"
#include "../../../GUI/GUI.h"
#include "../../../InputHandler/Input/Input.h"
class MenuState :
	public StateClass
{
public:
	MenuState();
	virtual ~MenuState();
	void Initialize();
	void Release();
	void Update(double deltaTime);
	void ProcessInput(double* deltatime);
	Input* input;
	void Render();
	bool exitMenu;
private:
	void OnEnter();
	void OnExit();
	GUI* mainUI;
	GUI* howToUI;
	Scene* menuScene;
	float time;


#pragma region variables for the buttons
	XMFLOAT2 Maxexit = { (float)(0.035f*WIN_WIDTH),(float)(0.825f*WIN_HEIGHT) };
	XMFLOAT2 Minexit = { (float)(0.195f*WIN_WIDTH),(float)(0.9375f*WIN_HEIGHT) };

	float Maxex = ((2.0f * Maxexit.x) / (float)WIN_HEIGHT - 1.0f);
	float Maxey = ((2.0f * -Maxexit.y) / (float)WIN_WIDTH + 1.0f);
	float Minex = ((2.0f * Minexit.x) / (float)WIN_HEIGHT - 1.0f);
	float Miney = ((2.0f * -Minexit.y) / (float)WIN_WIDTH + 1.0f);
	//NewGame
	XMFLOAT2 MaxNewGame = { (float)(0.035f*WIN_WIDTH), (float)(0.508f*WIN_HEIGHT) };
	XMFLOAT2 MinNewGame = { (float)(0.195f*WIN_WIDTH), (float)(0.625f*WIN_HEIGHT) };
	float Maxnx = ((2.0f * MaxNewGame.x) / (float)WIN_HEIGHT - 1.0f);
	float Maxny = ((2.0f * -MaxNewGame.y) / (float)WIN_WIDTH + 1.0f);
	float Minnx = ((2.0f * MinNewGame.x) / (float)WIN_HEIGHT - 1.0f);
	float Minny = ((2.0f * -MinNewGame.y) / (float)WIN_WIDTH + 1.0f);
	//Show the control UI 
	XMFLOAT2 MaxControls = { (float)(0.035f*WIN_WIDTH),(float)(0.6708f*WIN_HEIGHT) };
	XMFLOAT2 MinControls = { (float)(0.195f*WIN_WIDTH),(float)(0.783f*WIN_HEIGHT) };
	float Maxcx = ((2.0f * MaxControls.x) / (float)WIN_HEIGHT - 1.0f);
	float Maxcy = ((2.0f * -MaxControls.y) / (float)WIN_WIDTH + 1.0f);
	float Mincx = ((2.0f * MinControls.x) / (float)WIN_HEIGHT - 1.0f);
	float Mincy = ((2.0f * -MinControls.y) / (float)WIN_WIDTH + 1.0f);

	XMFLOAT2 ExitControlMAX = { (float)(0.0391f*WIN_WIDTH),(float)(0.88f*WIN_HEIGHT) };
	XMFLOAT2 ExitControlMIN = { (float)(0.1641f*WIN_WIDTH),(float)(0.9597f*WIN_HEIGHT) };
	float MaxEcx = ((2.0f * ExitControlMAX.x) / (float)WIN_HEIGHT - 1.0f);
	float MaxEcy = ((2.0f * -ExitControlMAX.y) / (float)WIN_WIDTH + 1.0f);
	float MinEcx = ((2.0f * ExitControlMIN.x) / (float)WIN_HEIGHT - 1.0f);
	float MinEcy = ((2.0f * -ExitControlMIN.y) / (float)WIN_WIDTH + 1.0f);
#pragma endregion

};

