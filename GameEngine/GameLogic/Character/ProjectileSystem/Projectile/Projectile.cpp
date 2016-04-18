#include "Projectile.h"



Projectile::Projectile()
{
}


Projectile::~Projectile()
{
}

void Projectile::Initialize()
{
	age = 5.0f;
	speed = 3.0f;
	dmgMultiplier = 2.0f;

	isFired = false;
	colided = false;
}

void Projectile::Release()
{

}
