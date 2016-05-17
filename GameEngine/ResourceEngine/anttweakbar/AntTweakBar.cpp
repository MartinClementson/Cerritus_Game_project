#include "AntTweakBar.h"



AntTweakBar::AntTweakBar()
{
}


AntTweakBar::~AntTweakBar()
{
}

void AntTweakBar::Initialize(ID3D11Device * gDevice)
{
	gMyBar = TwNewBar("Cerritus TweakBar");

	TwInit(TW_DIRECT3D11, gDevice);
	TwWindowSize(WIN_HEIGHT, WIN_WIDTH);
}

void AntTweakBar::Update()
{
	TwDraw();
}

void AntTweakBar::Release()
{
}
