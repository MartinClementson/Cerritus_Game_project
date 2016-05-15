#include "Pickup.h"



Pickup::Pickup()
{
}


PickupType Pickup::GetPickupType()
{
	return pickupType;
}

void Pickup::SetPickupType(PickupType pickup )
{
	this->pickupType = pickup;
}

Pickup::Pickup(XMFLOAT3 pos, PickupType pickup)
{
	graphics = Graphics::GetInstance();
	this->pickupType = pickup;
	this->position = pos;
	this->rotation = { 0,0,0 };
	Initialize();
	RenderInfo.position = this->position;

	if (pickup == PickupType::HEAL)
		RenderInfo.object = MeshEnum::PICKUP_HEAL;
	else if (pickup == PickupType::WEAPON)
		RenderInfo.object = MeshEnum::PICKUP_WEAPON;
	else
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
	respawnTimer = 0.0f;

}

void Pickup::Release()
{

}

void Pickup::Update(double deltaTime)
{
	if (isActive == false)
	{
		respawnTimer += (float)deltaTime;
	}

	if(respawnTimer >= 10.0f && this->pickupType == PickupType::Weapon)
	{
		isActive = true;
		respawnTimer = 0.0f;
	}

	if (respawnTimer >= 30.0f && this->pickupType == PickupType::Heal)
	{
		isActive = true;
		respawnTimer = 0.0f;
	}

	if (down == false)
	{
		position.y += 0.5f * (float)deltaTime;
		if (position.y > 2.0f)
		{
			down = true;
		}
	}
	else if(down == true)
	{
		position.y -= 0.5f * (float)deltaTime;
		if (position.y <= 1.0f)
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
