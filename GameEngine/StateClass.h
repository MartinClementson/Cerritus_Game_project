#pragma once
class StateClass
{
public:
	bool isActive;
	//Input userInput

public:
	StateClass();
	~StateClass();
	virtual void Update();
	virtual void Render();

	virtual void Initialize();
	virtual void Release();

	virtual void ProcessInput();

	virtual bool GetIsActive();
private:
	virtual void OnEnter();
	virtual void OnExit();
};
