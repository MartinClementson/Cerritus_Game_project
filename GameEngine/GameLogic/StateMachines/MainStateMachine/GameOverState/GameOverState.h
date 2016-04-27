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

private:
	void OnEnter();
	void OnExit();
private:
	Scene* GameOverScene;
	GUI* gameOverGUI;
	float points;
};

