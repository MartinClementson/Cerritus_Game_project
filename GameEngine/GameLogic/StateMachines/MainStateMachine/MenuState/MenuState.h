#pragma once
#include "../../StateClass/StateClass.h"
#include "../../../Scene/Scene.h"
#include "../../../GUI/GUI.h"
class MenuState :
	public StateClass
{
public:
	MenuState();
	virtual ~MenuState();
	void Initialize();
	void Release();
	void Update(double deltaTime);
	void Render();
private:
	void OnEnter();
	void OnExit();
private:
	GUI* mainUI;
	GUI* howToUI;
	Scene* menuScene;
};

