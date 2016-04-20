#pragma once
#include "StateMachines\MainStateMachine\MainStateMachine.h"
class Game
{
public:
	Game();
	virtual ~Game();
	void Initialize();
	void Release();
	void Update(double deltaTime);
	void Render();
private:
	MainStateMachine* stateMachine;

};