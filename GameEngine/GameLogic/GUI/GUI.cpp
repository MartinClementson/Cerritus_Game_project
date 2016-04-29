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
	size = { 0, 1 };
	position = { 0,5};
	grapichs = Graphics::GetInstance();
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
