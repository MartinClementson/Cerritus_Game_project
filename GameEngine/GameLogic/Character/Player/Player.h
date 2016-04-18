#pragma once
#include "../Character.h"
#include "../../../Source/LibIncluder.h"
#include "../../InputHandler/Input/Input.h"
#include "../ProjectileSystem/ProjectileSystem.h"
#include "../../../Enumerations/Enumerations.h"
#include "../../../Structs/RenderInfo.h"


class Player :
	public Character
{
public:
	Player();
	virtual ~Player();

	void Initialize();
	void Release();
	void Update(double deltaTime);
	void Render();
	void Move(MovementDirection dir, double deltaTime);
	void Shoot(InputKeys input, double deltaTime);


public:
	Input* userInput;
	

private:
	MeshEnum meshID;//enum
	RenderInfoChar renderInfo;
	ProjectileSystem* projectileSystem;
	//Collision();
};

