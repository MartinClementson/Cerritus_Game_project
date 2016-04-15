#pragma once
#include "../../../../../Source/LibIncluder.h"
class Particle
{
public:
	Particle();
	~Particle();
	void Initialize();
	void Release();
private:
	DirectX::XMFLOAT3 position, direction;
	float age, speed;
	bool isActive;
	//ParticlesType type;//enum
};

