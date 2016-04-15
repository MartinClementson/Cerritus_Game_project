#pragma once
#include "../../StateClass/StateClass.h"
#include "../../../Scene/Scene.h"
#include "../../../GUI/GUI.h"
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

