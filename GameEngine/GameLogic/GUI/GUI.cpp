#include "GUI.h"



GUI::GUI()
{
	items = new std::vector<GUIElement*>;
}


GUI::~GUI()
{
	delete items;
}

void GUI::Initialize()
{
	size = size;
	uv = uv;
	grapichs = Graphics::GetInstance();
	this->texture = texture;
}

void GUI::Release()
{

}

void GUI::Update(double deltaTime)
{
	renderInfo = { size,uv };		
	this->renderInfo.object = texture;
}

void GUI::Render()
{
	renderInfo = { size,uv };

	this->renderInfo.object = texture;

	grapichs->QueueRender(&renderInfo);
	
}

UITextures GUI::getUI()
{
	return texture;
}

XMFLOAT2 GUI::getPos()
{
	return uv;
}

void GUI::setPos(XMFLOAT2 position)
{
	this->uv = uv;
}

void GUI::setUI(UITextures texture)
{
	this->texture = texture;
}
