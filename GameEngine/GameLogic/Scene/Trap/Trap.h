#pragma once
#include "Animation.h"
#include "Model.h"
class Trap
{
public:
	Trap();
	virtual~Trap();
	virtual void Initialize();
	virtual void Release();
	virtual void Update(double deltaTime);
	virtual void Render();
	//Collision();
private:
	float damage;
	Animation* animation;
	Model* mesh;
};

