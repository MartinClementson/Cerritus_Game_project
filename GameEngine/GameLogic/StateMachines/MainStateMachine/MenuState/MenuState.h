#pragma once
#include "../../StateClass/StateClass.h"
#include "../../../Scene/Scene.h"
#include "../../../GUI/GUI.h"
#include "../../../InputHandler/Input/Input.h"
class MenuState :
	public StateClass
{
public:
	MenuState();
	virtual ~MenuState();
	void Initialize();
	void Release();
	void Update(double deltaTime);
	void ProcessInput(double* deltatime);
	Input* input;
	void Render();
	bool exitMenu;
private:
	void OnEnter();
	void OnExit();
private:
	GUI* mainUI;
	GUI* howToUI;
	Scene* menuScene;
};

