#include "Pickup.h"



Pickup::Pickup()
{
}


Pickup::Pickup(XMFLOAT3 pos)
{
	graphics = Graphics::GetInstance();
	this->position = pos;
	this->rotation = { 0,0,0 };
	Initialize();
	RenderInfo.position = this->position;
	RenderInfo.object = PLACEHOLDER;
}

Pickup::~Pickup()
{
}

void Pickup::Initialize()
{
	isActive = true;
	radius = 1.0f;
	down = false;
}

void Pickup::Release()
{

}

void Pickup::Update(double deltaTime)
{

	if (down == false)
	{
		position.y += 0.5 * deltaTime;
		if (position.y > 2)
		{
			down = true;
		}
	}
	else if(down == true)
	{
		position.y -= 0.5 * deltaTime;
		if (position.y <= 1)
		{
			down = false;
		}
	}


	RenderInfo.position = this->position;


}

void Pickup::Render()
{
	RenderInfo.position = this->position;
	if (this->isActive == true)
	{
		graphics->QueueRender(&this->RenderInfo);
	}
}

XMFLOAT3 Pickup::GetPosition()
{
	return position;
}

void Pickup::SetPosition(XMFLOAT3 pos)
{
	this->position = pos;
}

float Pickup::GetRadius()
{
	return radius;
}

bool Pickup::GetIsActive()
{
	return isActive;
}

void Pickup::SetIsActive(bool active)
{
	this->isActive = active;
}
