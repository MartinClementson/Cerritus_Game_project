#pragma once
#include <AntTweakBar.h>
#include "../../Source/Constants.h"
#include "../../Source/LibIncluder.h"
//#include "../../GameLogic/InputHandler/Input/Input.h"
class AntTweakBar
{
public:
	~AntTweakBar();

	void Initialize(ID3D11Device* gDevice);
	void Update();
	void Release();

	void toggleShowingBar();
#pragma region functions to add attributes to the tweakbar

	void addSlider(char* attributeName, float &connectedAttribute);

#pragma endregion

	static AntTweakBar* GetInstance();
	bool GetIfShown() { return this->showBar; }
private:
	AntTweakBar();
	TwBar *gMyBar;

	bool showBar = false;

};

