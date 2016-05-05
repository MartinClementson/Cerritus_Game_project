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
	//DevContext->ClearRenderTargetView();
			
	
	//numbers
	if (UITextures::NUMBERS)
	{
		size.x = 245.0f;

		size.y = 113.0f;

		this->renderInfo = { size,position };
		this->renderInfo.object = texture;
		//render numbers to different areas of the screen for different events. 
		//thinking of creating 3 quads on the screen, 1 for waves , 1 for enemys, 1 for ammo 
		//unsure on how to do this 
	}
	if (!UITextures::NUMBERS)
	{
		renderInfo = { size,position };
		this->renderInfo.object = texture;
	}
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

