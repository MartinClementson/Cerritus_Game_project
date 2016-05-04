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
	//items = new std::vector<GUIElement*>;
	size = size;
	position = position;
	grapichs = Graphics::GetInstance();
	texture = UITextures::MENU;
}

void GUI::Release()
{
}

void GUI::Update(double deltaTime)
{
	
	renderInfo = { size,position };		
	this->renderInfo.object = texture;
	
	
	


}

void GUI::Render()
{
	renderInfo = { size,position };

	this->renderInfo.object = texture;

	grapichs->QueueRender(&renderInfo);
	
}

UITextures GUI::getUI()
{
	return texture;
}

XMFLOAT2 GUI::getPos()
{
	return position;
}

void GUI::setPos(XMFLOAT2 position)
{
	this->position = position;
}

void GUI::setUI(UITextures texture)
{
	this->texture = texture;
}
