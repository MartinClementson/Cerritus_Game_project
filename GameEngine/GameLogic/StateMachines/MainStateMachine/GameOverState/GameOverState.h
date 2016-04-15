#pragma once
#include "StateClass.h"
#include "Scene.h"
#include "GUI.h"
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
private:
	void OnEnter();
	void OnExit();
private:
	Scene* GameOverScene;
	GUI* gameOverGUI;
};

