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
	size = { 0, 1,0 };
	position = { 0,5,0};
	grapichs = Graphics::GetInstance();
	this->renderInfo.object = UITextures::HUD;
}

void GUI::Release()
{
}

void GUI::Update(double deltaTime)
{
	
		
	renderInfo = { size,position };
	this->renderInfo.object = UITextures::HUD;


}

void GUI::Render()
{
	grapichs->QueueRender(&renderInfo);
	
}
