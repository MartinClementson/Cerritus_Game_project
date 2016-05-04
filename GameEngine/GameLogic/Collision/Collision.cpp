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

void Collision::AddTrap(BearTrap *bTrap)
{
	bearTrap.push_back(bTrap);
}

void Collision::ClearTraps()
{
	this->bearTrap.clear();
}

bool Collision::BearTrapPlayerCollision(BearTrap * trap)
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

bool Collision::PlayerProxyEnemy(Enemy * enemy)
{
	XMFLOAT3 playPos = player->GetPosition();
	float playRad = player->GetRadius();

	enemyPos = enemy->GetPosition();
	enemyRad = 40;

	if (pow(playPos.x - enemyPos.x, 2)
		+ pow(playPos.z - enemyPos.z, 2)
		< pow(playRad + enemyRad, 2))
	{
		return true;
	}
	return false;
}

bool Collision::BearTrapEnemyCollision(BearTrap * trap, Enemy * enemy)
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
			enemy->movementSpeed = 1.0f;
		}
		return true;
	}

	return false;
}


bool Collision::EnemyProxTrap(BearTrap * trap, Enemy * enemy)
{
	trapPos = trap->GetPosition();
	trapRad = 10;

	enemyPos = enemy->GetPosition();
	enemyRad = enemy->GetRadius();

	if (pow(trapPos.x - enemyPos.x, 2)
		+ pow(trapPos.z - enemyPos.z, 2)
		< pow(trapRad + enemyRad, 2))
	{
		if (trap->isActive)
		{
			enemy->movementSpeed = 10.0f;
		}
		return true;
	}

	return false;
}


bool Collision::FireTrapPlayerCollision(FireTrap * trap)
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

bool Collision::FireTrapEnemyCollision(FireTrap * trap, Enemy * enemy)
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
	float playRad = 2;
	
	enemyPos =  enemy->GetPosition();
	enemyRad = enemy->GetRadius();
	if (pow(playPos.x - enemyPos.x, 2) 
		+ pow(playPos.z - enemyPos.z, 2)
		< pow(playRad + enemyRad, 2)) 
	{
		if (enemy->isAlive && enemy->movementSpeed > 0)
		{
			enemy->movementSpeed = 0;
			player->SetHealth(player->GetHealth() - 15.0f);
		}
		return true;
	}

	return false;
}

bool Collision::PlayerDistanceCollision(Enemy* enemy)
{
	XMFLOAT3 playPos = player->GetPosition();
	float playRad = player->GetRadius2();

	enemyPos = enemy->GetPosition();
	enemyRad = enemy->GetRadius2();

	if (pow(playPos.x - enemyPos.x, 2)
		+ pow(playPos.z - enemyPos.z, 2)
		< pow(playRad + enemyRad, 2))
	{
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

bool Collision::EnemyCollision(Enemy* enemy, Enemy* enemys)
{
	enemyPos = enemy->GetPosition();
	enemyRad2 = enemy->GetRadius2();

	enemyPos2 = enemys->GetPosition();
	enemyRad3 = enemys->GetRadius2();

	if (pow(enemyPos2.x - enemyPos.x, 2)
		+ pow(enemyPos2.z - enemyPos.z, 2)
		< pow(enemyRad3 + enemyRad2, 2))
	{
		return true;
	}
	return false;
}

bool Collision::TrapandEnemyLottery(Enemy* enemys)
{
	for (size_t i = 0; i < this->bearTrap.size(); i++)
	{
		if (this->bearTrap.at(i)->isActive)
		{


			trapPos = this->bearTrap.at(i)->GetPosition();
			trapRad = this->bearTrap.at(i)->GetRadius2();

			enemyPos = enemys->GetPosition();
			enemyRad = enemys->GetRadius2();

			if (pow(trapPos.x - enemyPos.x, 2)
				+ pow(trapPos.z - enemyPos.z, 2)
				< pow(trapRad + enemyRad, 2))
			{
				return true;
			}
		}
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



