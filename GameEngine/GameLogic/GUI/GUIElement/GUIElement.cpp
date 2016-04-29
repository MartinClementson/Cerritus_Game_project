#include "GUIElement.h"



GUIElement::GUIElement()
{
}


GUIElement::~GUIElement()
{
}

void GUIElement::Initialize()
{
	this->position = position;
	this->size = size;
	grapichs = Graphics::GetInstance();
}

void GUIElement::Release()
{

}

void GUIElement::Update(double deltaTime)
{
	renderInfo = { size,position };
}

void GUIElement::Render()
{
	grapichs->QueueRender(&renderInfo);
}
