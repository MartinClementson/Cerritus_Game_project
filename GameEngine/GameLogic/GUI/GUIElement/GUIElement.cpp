#include "GUIElement.h"



GUIElement::GUIElement()
{
}


GUIElement::~GUIElement()
{
}

void GUIElement::Initialize()
{
	this->uv = uv;
	this->size = size;
	grapichs = Graphics::GetInstance();
}

void GUIElement::Release()
{

}

void GUIElement::Update(double deltaTime)
{
	renderInfo = { size,uv };

}

void GUIElement::Render()
{
	grapichs->QueueRender(&renderInfo);
}
