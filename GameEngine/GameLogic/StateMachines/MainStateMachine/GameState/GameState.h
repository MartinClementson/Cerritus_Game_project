#pragma once
#include "../../StateClass/StateClass.h"
#include "./DeathState/MainDeathState.h"
#include "./PausedState/MainPausedState.h"
#include "../../../Scene/Scene.h"
#include "../../../Character/Player/Player.h"
#include "../../../InputHandler/Input/Input.h"
#include "../../../GUI/GUI.h"
#include "../../../Character/Enemy/Enemy.h"
#include "../../../Collision/Collision.h"
#include "../../../../Source/GameTimer/GameTimer.h"
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
	bool isPlayerDead;
	void SetIsActive(bool isPlayerDead);
	bool GetIsActive();
	float timeSincePaused;
	int index;
	float GetPoints();


private:
	void OnEnter();
	void OnExit();
	
private:
	Scene* room1;
	Scene* room2;
	Player* player;
	//Enemy* enemy;
	Input* input;
	GUI* gameUI;
	MainPausedState* pause;
	MainDeathState* death;
	Collision* collision;
	GameTimer* gameTimer;
};

