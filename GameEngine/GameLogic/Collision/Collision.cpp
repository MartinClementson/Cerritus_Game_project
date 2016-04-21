#include "Collision.h"



Collision::Collision()
{

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

void Collision::AddPlayer(Player* player)
{
	
	this->player = player;
}

bool Collision::PlayerCollision(Enemy* enemy)
{
	XMFLOAT3 playPos = player->GetPosition();
	float playRad = player->GetRadius();
	
	XMFLOAT3 enemyPos =  enemy->GetPosition();
	float enemyRad = enemy->GetRadius();
	if (pow(playPos.x - enemyPos.x, 2) 
		+ pow(playPos.z - enemyPos.z, 2)
		< pow(playRad + enemyRad, 2)) 
	{
		return true;
	}

	return false;
}

Collision::~Collision()
{

}



