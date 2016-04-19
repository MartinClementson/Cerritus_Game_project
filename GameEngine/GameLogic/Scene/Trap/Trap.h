#pragma once
#include "../../Animation/Animation.h"
#include "../GameObject/Model/Model.h"
class Trap
{
public:
	Trap();
	virtual~Trap();
	virtual void Initialize();
	virtual void Release();
	virtual void Update(double deltaTime);
	virtual void Render();
	virtual float GetDamage();
	virtual void SetDamage(float damage);
	virtual DirectX::XMFLOAT3 GetPosition();
	virtual void SetPosition(DirectX::XMFLOAT3 position);  // la till virtual på get och set då de inte ska användas i denna klass
	//Collision();
private:
	DirectX::XMFLOAT3 position;
	float damage;
	Animation* animation;
	Model* mesh;
};

