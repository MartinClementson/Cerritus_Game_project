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
	this->numbers = numbers;
	amount = 0;
	
}

void GUI::Release()
{

}

void GUI::Update(double deltaTime)
{
	/*vtx[0] = { 0.003 ,0.597 };
	vtx[1] = { 0.129 ,0.597 };
	vtx[2] = { 0.129 ,0.403 };
	vtx[3] = { 0.003 ,0.403 };
	
	UVs.push_back(vtx);*/
	amount++;
	renderInfo = { size,uv };
	this->renderInfo.UIobject = texture;
	this->renderInfo.UInumber = numbers;
	
}

void GUI::Render()
{
	swagitt = { size,uv };
	this->swagitt.UIobject = texture;
	this->swagitt.UInumber = numbers;
	grapichs->QueueRender(&swagitt);

	renderInfo = { size,uv };
	this->renderInfo.UIobject = texture;
	this->renderInfo.UInumber = numbers;
	grapichs->QueueRender(&renderInfo);
	
	
	//grapichs->QueueRender(&renderInfo);
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

void GUI::setUINR(UiNumbers numbers)
{
	this->numbers = numbers;
}

