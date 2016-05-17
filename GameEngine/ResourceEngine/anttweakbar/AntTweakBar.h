#pragma once
#include <AntTweakBar.h>
#include "../../Source/Constants.h"
#include "../../Source/LibIncluder.h"
class AntTweakBar
{
public:
	~AntTweakBar();

	void Initialize(ID3D11Device* gDevice);
	void Update();
	void Release();

#pragma region functions to add attributes to the tweakbar
	void addSlider(char* attributeName, float* connectedAttribute);
#pragma endregion

	static AntTweakBar* GetInstance();
private:
	AntTweakBar();
	TwBar *gMyBar;
};

