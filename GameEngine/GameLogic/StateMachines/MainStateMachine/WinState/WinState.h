#pragma once
#include "../../StateClass/StateClass.h"
#include "../../../Scene/Scene.h"
#include "../../../GUI/GUI.h"
#include "../../../Character/Player/Player.h"
#include"../../../InputHandler/Input/Input.h"

class WinState :
	public StateClass
{
public:
	WinState();
	virtual ~WinState();
	void Initialize();
	void Release();
	void Update(double deltaTime);
	void Render();
	void ProcessInput(double* deltaTime);
	Input* input;
	bool replay;

	void SetPoints(float points);
	float GetPoints();
	void SetLastHigh(float high);
	bool toMenu;

private:
	void OnEnter();
	void OnExit();
	GUI* WinUI;
	float points;
	float lastHighscore;
#pragma region variables for menu
	XMFLOAT2 MaxNewGame = { (float)(0.7977f*(float)WIN_WIDTH),(float)(0.6319f*(float)WIN_HEIGHT) };
	XMFLOAT2 MinNewGame = { (float)(0.9844f*(float)WIN_WIDTH),(float)(0.7653f*(float)WIN_HEIGHT) };
	float Maxnx = ((2.0f * MaxNewGame.x) / (float)WIN_HEIGHT - 1.0f);
	float Maxny = ((2.0f * -MaxNewGame.y) / (float)WIN_WIDTH + 1.0f);
	float Minnx = ((2.0f * MinNewGame.x) / (float)WIN_HEIGHT - 1.0f);
	float Minny = ((2.0f * -MinNewGame.y) / (float)WIN_WIDTH + 1.0f);


	XMFLOAT2 MaxMenu = { (float)(0.7977f*(float)WIN_WIDTH),(float)(0.8153f*(float)WIN_HEIGHT) };
	XMFLOAT2 MinMenu = { (float)(0.9844f*(float)WIN_WIDTH),(float)(0.9514f*(float)WIN_HEIGHT) };
	float Maxmx = ((2.0f * MaxMenu.x) / (float)WIN_HEIGHT - 1.0f);
	float Maxmy = ((2.0f * -MaxMenu.y) / (float)WIN_WIDTH + 1.0f);
	float Minmx = ((2.0f * MinMenu.x) / (float)WIN_HEIGHT - 1.0f);
	float Minmy = ((2.0f * -MinMenu.y) / (float)WIN_WIDTH + 1.0f);
#pragma endregion
};

