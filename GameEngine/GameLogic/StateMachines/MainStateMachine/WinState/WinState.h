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
private:
	GUI* WinUI;
	float points;
	float lastHighscore;
};

