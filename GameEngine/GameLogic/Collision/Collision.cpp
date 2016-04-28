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

void Collision::AddTrap(FireTrap * fTraps,BearTrap *bTrap)
{
	fireTrap.push_back(fTraps);
	bearTrap.push_back(bTrap);
}

bool Collision::bearTrapPlayerCollision(BearTrap * trap)
{

	XMFLOAT3 playPos = player->GetPosition();
	float playRad = player->GetRadius();
	trapPos = trap->GetPosition();
	trapRad = trap->GetRadius();

	if (pow(playPos.x - trapPos.x, 2)
		+ pow(playPos.z - trapPos.z, 2)
		< pow(playRad + trapRad, 2))
	{
		if (trap->isActive)
		{
			player->VelocityMax = 0.2f;
			player->SetMulti(1);
		}
		return true;
		
	}

	return false;
}

bool Collision::PlayerProxyTrap(BearTrap * trap)
{

	XMFLOAT3 playPos = player->GetPosition();
	float playRad = player->GetRadius();

	trapPos = trap->GetPosition();
	trapRad = 5;

	if (pow(playPos.x - trapPos.x, 2)
		+ pow(playPos.z - trapPos.z, 2)
		< pow(playRad + trapRad, 2))
	{
		if (trap->isActive)
		{
			player->VelocityMax = 0.2f;
			player->SetMulti(1);
		}
		return true;

	}

	return false;
}

bool Collision::bearTrapEnemyCollision(BearTrap * trap, Enemy * enemy)
{
	trapPos = trap->GetPosition();
	trapRad = trap->GetRadius();

	enemyPos = enemy->GetPosition();
	enemyRad = enemy->GetRadius();

	if (pow(trapPos.x - enemyPos.x, 2)
		+ pow(trapPos.z - enemyPos.z, 2)
		< pow(trapRad + enemyRad, 2))
	{
		if (trap->isActive)
		{
			enemy->movementSpeed = 10.0f; // all hail the glorious satan
		}
		return true;
	}

	return false;
}

bool Collision::EnemyProxTrap(BearTrap * trap, Enemy * enemy)
{
	trapPos = trap->GetPosition();
	trapRad = 5;

	enemyPos = enemy->GetPosition();
	enemyRad = enemy->GetRadius();

	if (pow(trapPos.x - enemyPos.x, 2)
		+ pow(trapPos.z - enemyPos.z, 2)
		< pow(trapRad + enemyRad, 2))
	{
		if (trap->isActive)
		{
			enemy->movementSpeed = 10.0f; // all hail the glorious satan
		}
		return true;
	}

	return false;
}

bool Collision::fireTrapPlayerCollision(FireTrap * trap)
{

	XMFLOAT3 playPos = player->GetPosition();
	float playRad = player->GetRadius();
	trapPos = trap->GetPosition();
	trapRad = trap->GetRadius();

	if (pow(playPos.x - trapPos.x, 2)
		+ pow(playPos.z - trapPos.z, 2)
		< pow(playRad + trapRad, 2))
	{
		if (trap->isActive)
		{
			player->DoT = trap->GetDot();
		}
 		return true;

	}
	return false;
}

bool Collision::fireTrapEnemyCollision(FireTrap * trap, Enemy * enemy)
{
	trapPos = trap->GetPosition();
	trapRad = trap->GetRadius();

	enemyPos = enemy->GetPosition();
	enemyRad = enemy->GetRadius();

	if (pow(trapPos.x - enemyPos.x, 2)
		+ pow(trapPos.z - enemyPos.z, 2)
		< pow(trapRad + enemyRad, 2))
	{
		if (trap->isActive)
		{
			enemy->DoT = trap->GetDot();
		}
		return true;
	}

	return false;
}

bool Collision::PlayerCollision(Enemy* enemy)
{
	XMFLOAT3 playPos = player->GetPosition();
	float playRad = player->GetRadius();
	
	enemyPos =  enemy->GetPosition();
	enemyRad = enemy->GetRadius();
	if (pow(playPos.x - enemyPos.x, 2) 
		+ pow(playPos.z - enemyPos.z, 2)
		< pow(playRad + enemyRad, 2)) 
	{
		if (enemy->isAlive)
		{
			player->SetHealth(player->GetHealth() - 10);
		}
		return true;
	}

	return false;
}

bool Collision::ProjectileEnemyCollision(Projectile* projectile,Enemy* enemy)
{
	XMFLOAT3 proPos = projectile->GetPos();
	float proRad = projectile->GetRadius();

	enemyPos = enemy->GetPosition();
	enemyRad = enemy->GetRadius();
	if (pow(proPos.x - enemyPos.x, 2)
		+ pow(proPos.z - enemyPos.z, 2)
		< pow(proRad + enemyRad, 2))
	{
		return true;
	}

	return false;
}

Collision::~Collision()
{

}

Player* Collision::GetPlayer()
{
	return this->player;
}



