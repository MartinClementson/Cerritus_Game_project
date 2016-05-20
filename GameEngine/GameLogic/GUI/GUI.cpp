#include "GUI.h"



GUI::GUI()
{
	grapichs = Graphics::GetInstance();
	renderInfo.size = this->size;
	renderInfo.uv = this->uv;
	renderInfo.UIobject = texture;
	renderInfo.UInumber = this->numbers;
}

GUI::GUI(UITextures texture)
{

}


GUI::~GUI()
{
	
}

void GUI::Initialize()
{
	this->size = { 1.0f,1.0f,0.0f };
	this->uv = { 1.0f,1.0f,0.0f };
	grapichs = Graphics::GetInstance();
	this->texture = UITextures::HUD;
	this->numbers = numbers;
}

void GUI::Release()
{

}

void GUI::Update(double deltaTime)
{

	renderInfo.size = this->size;
	renderInfo.uv = this->uv;
	renderInfo.UIobject = this->texture;
	renderInfo.UInumber = this->numbers;
	

}

void GUI::Render()
{
	grapichs = Graphics::GetInstance();
	renderInfo.size = this->size;
	renderInfo.uv = this->uv;
	renderInfo.UIobject = texture;
	renderInfo.UInumber = this->numbers;
	
	grapichs->QueueRender(&renderInfo);
}

UITextures GUI::getUI()
{
	return texture;
}

XMFLOAT3 GUI::getPos()
{
	return uv;
}

void GUI::setPos(XMFLOAT3 position)
{
	this->uv = position;
}

void GUI::setUI(UITextures texture)
{ 
	this->texture = texture;
}

void GUI::setUINR(UiNumbers numbers)
{
	this->numbers = numbers;
}

