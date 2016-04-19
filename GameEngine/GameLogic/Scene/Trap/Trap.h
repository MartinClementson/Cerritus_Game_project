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
	float GetDamage();
	void SetDamage(float damage);
	DirectX::XMFLOAT3 GetPosition();
	void SetPosition(DirectX::XMFLOAT3 position);
	//Collision();
private:
	DirectX::XMFLOAT3 position;
	float damage;
	Animation* animation;
	Model* mesh;
};

