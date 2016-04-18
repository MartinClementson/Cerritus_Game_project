#pragma once
#include "../GameObject.h"
#include "Particle/Particle.h"

class ParticleEmmiter :
	public GameObject
{
public:
	ParticleEmmiter();
	~ParticleEmmiter();
	void Initialize();
	void Release();
	void Update(double deltaTime);
	void Render();
	Particle EmmitParticle();
private:
	std::vector<Particle>* particles;
	float lifeSpan;
	int maxParticles;
};

