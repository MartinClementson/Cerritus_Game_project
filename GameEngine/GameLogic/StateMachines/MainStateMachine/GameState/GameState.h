#pragma once
#include "../../StateClass/StateClass.h"
#include "./DeathState/MainDeathState.h"
#include "./PausedState/MainPausedState.h"
#include "../../../Scene/Scene.h"
#include "../../../Character/Player/Player.h"
#include "../../../InputHandler/Input/Input.h"
#include "../../../GUI/GUI.h"
#include "../../../Character/Enemy/Enemy.h"

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
	void ProcessInput(double* deltaTime);

private:
	void OnEnter();
	void OnExit();
	
private:
	Scene* room1;
	Scene* room2;
	Player* player;
	Enemy* enemy;
	Input* input;
	GUI* gameUI;
	EnemyStateMachine* enemyState;
	MainPausedState* pause;
	MainDeathState* death;

};

