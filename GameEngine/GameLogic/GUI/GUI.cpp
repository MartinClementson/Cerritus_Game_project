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
	size = { 1,1,1 };
	position = { 0,4,0 };
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

void GUI::setUI(UITextures texture)
{
	this->texture = texture;
}
