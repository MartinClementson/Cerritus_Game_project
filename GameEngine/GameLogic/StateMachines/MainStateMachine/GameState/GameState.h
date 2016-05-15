#pragma once
#include "../../StateClass/StateClass.h"
#include "./DeathState/MainDeathState.h"
#include "./PausedState/MainPausedState.h"
#include "../MenuState/MenuState.h"
#include "../../../Scene/Scene.h"
#include "../../../Character/Player/Player.h"
#include "../../../InputHandler/Input/Input.h"
#include "../../../GUI/GUI.h"
#include "../../../Character/Enemy/Enemy.h"
#include "../../../Collision/Collision.h"
#include "../../../../Source/GameTimer/GameTimer.h"
#include "../../AudioManager/AudioManager.h"
#include "../../../Scene/Waves/Waves.h"

class GameState :
	public StateClass
{
public:
	GameState();
	virtual ~GameState();
	void Initialize(AudioManager* audioManager);
	void Release();
	void Update(double deltaTime);
	void Render();
	void ProcessInput(double* deltaTime);
	bool isPlayerDead;
	void SetIsActive(bool isPlayerDead);
	bool GetIsActive();
	float timeSincePaused;
	float index;
	float GetPoints();
	bool toWin = false;
	bool winBool = false;
	//EnemyBase* ClosestHealer(vector<EnemyBase*> healers);
	bool toMenu;

private:
	void OnEnter();
	void OnExit();

private:

	vector<EnemyBase*> healers;
	vector<BearTrap*> bearTraps;
	vector<FireTrap*> fireTraps;

	Scene* room1;
	Scene* room2;
	Player* player;
	Waves waves;
	int enemiesHealing;
	int nrOfHealers;
	//Enemy* enemy;
	Input* input;
	GUI* gameUI;
	MainPausedState* pause;
	MainDeathState* death;
	MenuState* menu;
	Collision* collision;
	GameTimer* gameTimer;
	AudioManager* audioManager;
};