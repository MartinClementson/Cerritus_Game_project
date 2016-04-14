#pragma once
#include "StateClass.h"
#include "Scene.h"
//#include "GUI.h"
class MenuState :
	public StateClass
{
public:
	MenuState();
	~MenuState();
	void Initialize();
	void Release();
	void Update(double deltaTime);
	void Render();
private:
	void OnEnter();
	void OnExit();
private:
	//GUI* mainUI;
	//GUI* howToUI
	Scene* menuScene;
};

