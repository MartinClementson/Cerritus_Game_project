#pragma once
#include "../../StateClass/StateClass.h"
#include "../../../Scene/Scene.h"
#include "../../../GUI/GUI.h"
#include "../../../Character/Player/Player.h"
#include"../../../InputHandler/Input/Input.h"
class GameOverState :
	public StateClass
{
public:
	GameOverState();
	virtual ~GameOverState();
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
	float GetLastHigh();
	void SetHighPlacing();
	bool toMenu;
	void getRenderScreen(UITextures* uiEnum, RenderInstructions* toRender);


private:
	void OnEnter();
	void OnExit();
	void SetPointPlacing();
	int GetNumber1();
	int GetNumber2();
	int GetNumber3();

	void SetLastHighScoreNumbers(int HN1, int HN2, int HN3);

	int GetScoreNumber1();
	int GetScoreNumber2();
	int GetScoreNumber3();

	void QuadNumberPick(int cases);
	void QuadNumberPick1(int cases);
	void QuadNumberPick2(int cases);

	void QuadNumberPickScore(int cases);
	void QuadNumberPickScore1(int cases);
	void QuadNumberPickScore2(int cases);

	Scene* GameOverScene;
	GUI* gameOverGUI;
	int test ;
	float points;
	float lastHighscore;

	float number;
	float number1;
	float number2;
	float number3;

	float highNumber;
	float highNumber1;
	float highNumber2;
	float highNumber3;
	int cases = 0;


	Graphics* graphics;
	RenderInfoUI gameover;
	RenderInfoUI gameover2;
	RenderInfoUI gameover3;
	RenderInfoUI gameover4;

	RenderInfoUI gameover5;
	RenderInfoUI gameover6;
	RenderInfoUI gameover7;


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

