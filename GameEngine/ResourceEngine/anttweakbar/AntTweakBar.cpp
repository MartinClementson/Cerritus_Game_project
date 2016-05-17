#include "AntTweakBar.h"



AntTweakBar::AntTweakBar()
{ 
}


AntTweakBar::~AntTweakBar()
{
}

void AntTweakBar::Initialize(ID3D11Device * gDevice)
{

	TwInit(TW_DIRECT3D11, gDevice);
	TwWindowSize((int)WIN_HEIGHT, (int)WIN_WIDTH);
	
	gMyBar = TwNewBar("Cerritus TweakBar");
	
}

void AntTweakBar::Update()
{
	if (showBar)
		TwDraw();
}

void AntTweakBar::Release()
{
	TwTerminate();
}

void AntTweakBar::toggleShowingBar()
{
	if (showBar)
		showBar = false;
	else
		showBar = true;
}

void AntTweakBar::addSlider(char * attributeName, float * connectedAttribute)
{
	TwAddVarRW(gMyBar, attributeName, TW_TYPE_FLOAT, &connectedAttribute, "");
}

AntTweakBar * AntTweakBar::GetInstance()
{
	static AntTweakBar instance;
	return &instance;
}
