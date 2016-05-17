#pragma once
#include <AntTweakBar.h>
#include "../../Source/Constants.h"
#include "../../Source/LibIncluder.h"
class AntTweakBar
{
public:
	AntTweakBar();
	~AntTweakBar();

	void Initialize(ID3D11Device* gDevice);
	void Update();
	void Release();
private:
	TwBar *gMyBar;
};

