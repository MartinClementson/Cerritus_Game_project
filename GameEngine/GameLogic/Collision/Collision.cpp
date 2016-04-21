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

void Collision::AddEnemy(Enemy* enemy, int index, int listCapacity)
{
	if (!enemyInit)
	{
		enemyBox.resize(listCapacity);
		for (int i = 0; i < enemyBox.size(); i++)
		{
			enemyBox.at(i) = NULL;
		}
	}
	enemyBox.insert(enemyBox.begin()+index, enemy);
}

void Collision::RemoveEnemy(int index)
{
	enemyBox.erase(enemyBox.begin() + index);
}

void Collision::AddPlayer(Player* player)
{
	if (!player)
	{
		this->player = player;
	}
}

bool Collision::PlyerCollision()
{
	return false;
}

Collision::~Collision()
{

}



