#pragma once
#include "StateClass.h"
#include "MainDeathState.h"
#include "MainPausedState.h"
#include "Scene.h"
#include "Player.h"
#include "Input.h"
#include "GUI.h"

class GameState :
	public StateClass
{
public:
	GameState();
	virtual ~GameState();
	void Initialize();
	void Release();
	void Update(double deltaTime);
	void Render();

private:
	void OnEnter();
	void OnExit();
	void ProcessInput(double deltaTime);
private:
	Scene* room1;
	Scene* room2;
	Player* player;
	Input* input;
	GUI* gameUI;
	MainPausedState* pause;
	MainDeathState* death;

};

