#include "Collision.h"



Collision::Collision()
{
	center = XMFLOAT3(0.0f, 0.0f, 0.0f);
	radius = 0;
}

Collision* Collision::GetInstance()
{
	static Collision instance;
	return &instance;
}

void Collision::AddEnemy(Enemy* enemy)
{
	enemyBox.push_back(enemy);
}

Collision::~Collision()
{

}

//Collision::Collision(float radius)
//{
//	this->radius = radius;
//}
//
//Collision::Collision(XMFLOAT3 center, float radius)
//{
//	this->center = center;
//	this->radius = radius;
//}

