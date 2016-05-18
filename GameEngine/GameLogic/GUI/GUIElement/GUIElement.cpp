#include "GUIElement.h"



GUIElement::GUIElement()
{



}


GUIElement::~GUIElement()
{
}

void GUIElement::Initialize()
{
	this->uv = { 0.0f,0.0f,0.0f };
	this->size = { 0.0f,0.0f,0.0f };
	grapichs = Graphics::GetInstance();
	texture = texture;
	numbers = numbers;
}

void GUIElement::Release()
{

}

void GUIElement::Update(double deltaTime)
{
	renderInfo = { size,uv };

	renderInfo.UIobject = texture;
	renderInfo.UInumber = numbers;
}

void GUIElement::Render()
{

	renderInfo.size = size;
	renderInfo.uv = uv;

	grapichs->QueueRender(&renderInfo);
}

void GUIElement::setUI(UITextures texture)
{

	this->texture = texture;

}

void GUIElement::setUINR(UiNumbers numbers)
{

	this->numbers = numbers;

}
