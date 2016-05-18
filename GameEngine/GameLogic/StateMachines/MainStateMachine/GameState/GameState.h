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
	void NewGame();
	bool toWin = false;
	bool winBool = false;
	//EnemyBase* ClosestHealer(vector<EnemyBase*> healers);
	bool toMenu;

private:
	void OnEnter();
	void OnExit();

private:
	Graphics * grapichs;

	

	vector<EnemyBase*> healers;
	vector<BearTrap*> bearTraps;
	vector<FireTrap*> fireTraps;

	Scene* room1;
	Scene* room2;
	Player* player;
	Waves waves;
	int enemiesHealing;
	int nrOfHealers;

	//for the traps
	float currentTime;

	//Enemy* enemy;
	Input* input;
	GUI* gameUI;
	MainPausedState* pause;
	MainDeathState* death;
	MenuState* menu;
	Collision* collision;
	GameTimer* gameTimer;
	AudioManager* audioManager;
	MainStates activeState;//enum


#pragma region variables for pausemenu


	XMFLOAT2 Maxexit = { (float)(0.384f*(float)WIN_WIDTH), (float)(0.6361f*(float)WIN_HEIGHT) };
	XMFLOAT2 Minexit = { (float)(0.618f*(float)WIN_WIDTH), (float)(0.7167f*(float)WIN_HEIGHT) };

	float Maxex = ((2.0f * Maxexit.x) / (float)WIN_HEIGHT - 1.0f);
	float Maxey = ((2.0f * -Maxexit.y) / (float)WIN_WIDTH + 1.0f);
	float Minex = ((2.0f * Minexit.x) / (float)WIN_HEIGHT - 1.0f);
	float Miney = ((2.0f * -Minexit.y) / (float)WIN_WIDTH + 1.0f);


	XMFLOAT2 MaxResumeGame = { (float)(0.384f*(float)WIN_WIDTH), (float)(0.3014f*(float)WIN_HEIGHT) };
	XMFLOAT2 MinResumeGame = { (float)(0.618f*(float)WIN_WIDTH), (float)(0.3819f*(float)WIN_HEIGHT) };

	float Maxnx = ((2.0f * MaxResumeGame.x) / (float)WIN_HEIGHT - 1.0f);
	float Maxny = ((2.0f * -MaxResumeGame.y) / (float)WIN_WIDTH + 1.0f);
	float Minnx = ((2.0f * MinResumeGame.x) / (float)WIN_HEIGHT - 1.0f);
	float Minny = ((2.0f * -MinResumeGame.y) / (float)WIN_WIDTH + 1.0f);

	XMFLOAT2 MaxRestart = { (float)(0.384f*(float)WIN_WIDTH),(float)(0.4625f*(float)WIN_HEIGHT) };
	XMFLOAT2 MinRestart = { (float)(0.618f*(float)WIN_WIDTH),(float)(0.5431f*(float)WIN_HEIGHT) };

	float Maxcx = ((2.0f * MaxRestart.x) / (float)WIN_HEIGHT - 1.0f);
	float Maxcy = ((2.0f * -MaxRestart.y) / (float)WIN_WIDTH + 1.0f);
	float Mincx = ((2.0f * MinRestart.x) / (float)WIN_HEIGHT - 1.0f);
	float Mincy = ((2.0f * -MinRestart.y) / (float)WIN_WIDTH + 1.0f);
#pragma endregion
};