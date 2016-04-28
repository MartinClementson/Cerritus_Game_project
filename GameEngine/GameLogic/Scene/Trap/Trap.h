#pragma once
#include "../../Animation/Animation.h"
#include "../GameObject/Model/Model.h"
#include "../../../Structs/RenderInfo.h"
#include "../../../ResourceEngine/Graphics/Graphics.h"
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
	virtual XMFLOAT3 GetPosition();
	virtual XMFLOAT3 GetRotation();
	virtual void SetPosition(DirectX::XMFLOAT3 position);  // la till virtual på get och set då de inte ska användas i denna klass
	virtual void SetRotation(DirectX::XMFLOAT3 rotation);
	virtual float GetRadius() { return this->radius; }
	virtual float GetRadius2() { return this->radius; }


	void initTrap();
	bool isActive;
	//Collision();
private:	
	Animation* animation;
	Model* mesh;
	RenderInfoTrap renderInfo;
	Graphics* grapichs;
protected:
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 rotation;
	float damage;
	float radius, radius2;
	
};

