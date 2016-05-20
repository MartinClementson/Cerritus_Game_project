#include "Collision.h"
#include <DirectXMath.h>
#include <complex>
inline DirectX::XMFLOAT3 operator-(DirectX::XMFLOAT3 a, DirectX::XMFLOAT3 b) {
	DirectX::XMFLOAT3 result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;

	return result;
}
inline DirectX::XMFLOAT3 operator+(DirectX::XMFLOAT3 a, float b) {
	DirectX::XMFLOAT3 result;

	result.x = a.x + b;
	result.y = a.y + b;
	result.z = a.z + b;

	return result;
}
Collision::Collision()
{

}

Collision* Collision::GetInstance()
{
	static Collision instance;
	
	return &instance;
}

void Collision::AddEnemy(EnemyBase* enemy)
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

void Collision::InitSceneCol()
{
	SceneCollision temp;

	//INNIES
	temp.Pos = { -5.445f,0.0f,12.777f };
	temp.Rad = 102.5f;
	this->SceneBoxesIn.push_back(temp);
	temp.Pos = { 62.0f,0.0f,-54.652f };
	temp.Rad = 65.086f;
	this->SceneBoxesIn.push_back(temp);
	temp.Pos = { -38.232f,0.0f,-29.303f };
	temp.Rad = 71.180f;
	this->SceneBoxesIn.push_back(temp);
	temp.Pos = { -1.506f,0.0f,-90.752f };
	temp.Rad = 22.259f;
	this->SceneBoxesIn.push_back(temp);
	temp.Pos = { 99.089f,0.0f,-76.505f };
	temp.Rad = 36.290f;
	this->SceneBoxesIn.push_back(temp);
	temp.Pos = { 55.924f,0.0f,62.290f };
	temp.Rad = 52.432f;
	this->SceneBoxesIn.push_back(temp);
	temp.Pos = { 24.232f,0.0f,138.911f };
	temp.Rad = 51.298f;
	this->SceneBoxesIn.push_back(temp);
	temp.Pos = { -34.080f,0.0f,126.460f };
	temp.Rad = 58.343f;
	this->SceneBoxesIn.push_back(temp);
	temp.Pos = { -73.772f,0.0f,58.492f };
	temp.Rad = 48.152f;
	this->SceneBoxesIn.push_back(temp);
	temp.Pos = { 11.490f,0.0f,261.287f };
	temp.Rad = 47.255f;
	this->SceneBoxesIn.push_back(temp);
	temp.Pos = { -42.841f,0.0f,264.170f };
	temp.Rad = 36.936f;
	this->SceneBoxesIn.push_back(temp);
	temp.Pos = { -8.590f,0.0f,221.689f };
	temp.Rad = 72.493f;
	this->SceneBoxesIn.push_back(temp);
	temp.Pos = { 72.552f,0.0f,113.852f };
	temp.Rad = 9.176f;
	this->SceneBoxesIn.push_back(temp);
	//OUTIES
	temp.Pos = { 3.276f,0.0f,221.908f };
	temp.Rad = 23.936f;
	this->SceneBoxesOut.push_back(temp);

	temp.Pos = { 40.538f,0.0f,11.178f };
	temp.Rad = 11.855f;
	this->SceneBoxesOut.push_back(temp);

	temp.Pos = { 12.664f,0.0f,122.685f };
	temp.Rad = 26.941f;
	this->SceneBoxesOut.push_back(temp);

	temp.Pos = { 22.423f,0.0f,141.494f };
	temp.Rad = 22.970f;
	this->SceneBoxesOut.push_back(temp);

	temp.Pos = { -13.852f,0.0f,97.801f };
	temp.Rad = 35.350f;
	this->SceneBoxesOut.push_back(temp);

	temp.Pos = { -26.961f,0.0f,72.470f };
	temp.Rad = 31.690f;
	this->SceneBoxesOut.push_back(temp);

	temp.Pos = { -32.308f,0.0f,-20.143f };
	temp.Rad = 11.547f;
	this->SceneBoxesOut.push_back(temp);

	temp.Pos = { -42.872f,0.0f,-9.671f };
	temp.Rad = 11.547f;
	this->SceneBoxesOut.push_back(temp);

	temp.Pos = { -34.144f,0.0f,-5.718f };
	temp.Rad = 6.714f;
	this->SceneBoxesOut.push_back(temp);

	temp.Pos = { -22.620f,0.0f,-28.909f };
	temp.Rad = 8.454f;
	this->SceneBoxesOut.push_back(temp);

	temp.Pos = { 37.501f,0.0f,-20.703f };
	temp.Rad = 14.714f;
	this->SceneBoxesOut.push_back(temp);

	temp.Pos = { 43.469f,0.0f,-7.348f };
	temp.Rad = 20.547f;
	this->SceneBoxesOut.push_back(temp);

	temp.Pos = { 155.137f,0.0f,-32.193f };
	temp.Rad = 40.294f;
	this->SceneBoxesOut.push_back(temp);

	temp.Pos = { 139.331f,0.0f,15.815f };
	temp.Rad = 46.945f;
	this->SceneBoxesOut.push_back(temp);

	temp.Pos = { 157.939f,0.0f,-118.095f };
	temp.Rad = 46.945f;
	this->SceneBoxesOut.push_back(temp);

	temp.Pos = { -108.330f,0.0f,7.827f };
	temp.Rad = 24.011f;
	this->SceneBoxesOut.push_back(temp);

	temp.Pos = { -125.518f,0.0f,24.114f };
	temp.Rad = 24.440f;
	this->SceneBoxesOut.push_back(temp)
		;
	temp.Pos = { -137.284f,0.0f,106.843f };
	temp.Rad = 49.330f;
	this->SceneBoxesOut.push_back(temp);

	temp.Pos = { -102.335f,0.0f,186.544f };
	temp.Rad = 40.815f;
	this->SceneBoxesOut.push_back(temp);

	temp.Pos = { -43.975f,0.0f,185.027f };
	temp.Rad = 5.0f;
	this->SceneBoxesOut.push_back(temp);

	temp.Pos = { 108.338f,0.0f,49.564f };
	temp.Rad = 14.393f;
	this->SceneBoxesOut.push_back(temp);

	temp.Pos = { 95.422f,0.0f,82.470f };
	temp.Rad = 7.769f;
	this->SceneBoxesOut.push_back(temp);

	temp.Pos = { 107.526f,0.0f,131.769f };
	temp.Rad = 36.876f;
	this->SceneBoxesOut.push_back(temp);

	temp.Pos = { 71.686f,0.0f,250.520f };
	temp.Rad = 22.970f;
	this->SceneBoxesOut.push_back(temp);

	temp.Pos = { -28.161f,0.0f,324.447f };
	temp.Rad = 37.605f;
	this->SceneBoxesOut.push_back(temp);

	temp.Pos = { 29.909f,0.0f,316.087f };
	temp.Rad = 16.575f;
	this->SceneBoxesOut.push_back(temp);

	temp.Pos = { 62.971f,0.0f,181.708f };
	temp.Rad = 12.292f;
	this->SceneBoxesOut.push_back(temp);

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
		if (trap->GetState()->GetTrapState() != TrapState::TRAP_INACTIVE_STATE)
		{
			player->VelocityMax = 0.2f;
			player->SetMulti(1);
		}
		return true;

	}

	return false;
}

bool Collision::BearTrapActivation(BearTrap * trap)
{

	XMFLOAT3 playPos = player->GetPosition();
	float playRad = player->GetRadius();

	trapPos = trap->GetPosition();
	trapRad = 10;

	if (pow(playPos.x - trapPos.x, 2)
		+ pow(playPos.z - trapPos.z, 2)
		< pow(playRad + trapRad, 2))
	{
		return true;
	}
	return false;
}

bool Collision::FireTrapActivation(FireTrap * trap)
{

	XMFLOAT3 playPos = player->GetPosition();
	float playRad = player->GetRadius();

	trapPos = trap->GetPosition();
	trapRad = 20;

	if (pow(playPos.x - trapPos.x, 2)
		+ pow(playPos.z - trapPos.z, 2)
		< pow(playRad + trapRad, 2))
	{
		return true;
	}
	return false;
}

bool Collision::PlayerProxyEnemy(EnemyBase * enemy)
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

bool Collision::HealerProximity(EnemyBase* enemy,EnemyBase* healer)
{

	XMFLOAT3 enemyPos = enemy->GetPosition();
	float enemyRad = enemy->GetRadius();

	XMFLOAT3 healerPos = healer->GetPosition();
	float healerRad = 5;

	if (pow(enemyPos.x - healerPos.x, 2)
		+ pow(enemyPos.z - healerPos.z, 2)
		< pow(enemyRad + healerRad, 2))
	{
		
       		return true;

	}

	return false;
}

bool Collision::BearTrapEnemyCollision(BearTrap * trap, EnemyBase * enemy)
{
	trapPos = trap->GetPosition();
	trapRad = trap->GetRadius();

	enemyPos = enemy->GetPosition();
	enemyRad = enemy->GetRadius();

	if (pow(trapPos.x - enemyPos.x, 2)
		+ pow(trapPos.z - enemyPos.z, 2)
		< pow(trapRad + enemyRad, 2))
	{
		if (trap->GetState()->GetTrapState() != TrapState::TRAP_INACTIVE_STATE && enemy->GetCharType() != CharacterType::HEALER)
		{
			enemy->movementSpeed = 1.0f;
		}
		return true;
	}

	return false;
}


bool Collision::EnemyProxTrap(BearTrap * trap, EnemyBase * enemy)
{
	trapPos = trap->GetPosition();
	trapRad = 10;

	enemyPos = enemy->GetPosition();
	enemyRad = enemy->GetRadius();

	if (pow(trapPos.x - enemyPos.x, 2)
		+ pow(trapPos.z - enemyPos.z, 2)
		< pow(trapRad + enemyRad, 2))
	{
		if (trap->isActive && enemy->GetCharType() != CharacterType::HEALER)
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
		if (trap->GetState()->GetTrapState() != TrapState::TRAP_INACTIVE_STATE)
		{
			player->DoT = 10.0f;
		}
 		return true;

	}
	return false;
}

bool Collision::FireTrapEnemyCollision(FireTrap * trap, EnemyBase * enemy)
{
	trapPos = trap->GetPosition();
	trapRad = trap->GetRadius();

	enemyPos = enemy->GetPosition();
	enemyRad = enemy->GetRadius();

	if (pow(trapPos.x - enemyPos.x, 2)
		+ pow(trapPos.z - enemyPos.z, 2)
		< pow(trapRad + enemyRad, 2))
	{
		if (trap->GetState()->GetTrapState() != TrapState::TRAP_INACTIVE_STATE)
		{
			enemy->DoT = trap->GetDot();
		}
		return true;
	}

	return false;
}

bool Collision::PlayerCollision(EnemyBase* enemy)
{
	XMFLOAT3 playPos = player->GetPosition();
	float playRad = 2;
	
	enemyPos =  enemy->GetPosition();
	enemyRad = enemy->GetRadius();
	if (pow(playPos.x - enemyPos.x, 2)
		+ pow(playPos.z - enemyPos.z, 2)
		< pow(playRad + enemyRad, 2))
	{
		if (enemy->isAlive && enemy->movementSpeed > 0) //kolla in denna senare, tima attack med animation
		{
			enemy->movementSpeed = 0;
			player->DowngradeWeapon();
			player->SetHealth(player->GetHealth() - 15.0f);
			AudioManager::GetInstance()->playPlayerHit();
		}
		return true;
	}
	return false;
}

bool Collision::SceneColIn(double deltaTime)
{
	XMFLOAT3 playerPos = player->GetPosition();
	XMFLOAT3 playFuturePos = player->GetPosition();
	float playRad = 2;

	XMFLOAT3 tempDir = player->GetDirection();
	Vec3 tempAcc = player->GetAcceleration();
	Vec3 tempVel = player->GetVelocity();
	float tempFalloff = player->GetFalloffFactor();

	tempVel.x += tempAcc.x * (float)deltaTime - tempVel.x * tempFalloff * (float)deltaTime;
	tempVel.y = 0.0f;
	tempVel.z += tempAcc.z * (float)deltaTime - tempVel.z * tempFalloff * (float)deltaTime;


	float currentVelo = tempVel.Length();

	if (currentVelo > player->VelocityMax)
	{

		Vec3 normalizer = tempVel.Normalize();
		normalizer = normalizer * player->VelocityMax;
		tempVel = normalizer;
	}

	if (currentVelo > 0.05f)
	{
		playFuturePos.x += tempVel.x;
		playFuturePos.y = Y_OFFSET;
		playFuturePos.z += tempVel.z;
	}
	//bool hitx = true;
	//bool hitz = true;
	//XMVECTOR tempX;
	//XMVECTOR tempZ;
	////(pow(playFuturePos.x - SceneBoxesIn.at(i).Pos.x, 2) + pow(playFuturePos.z - SceneBoxesIn.at(i).Pos.z, 2) < pow(playRad + SceneBoxesIn.at(i).Rad, 2))
	////(pow(playFuturePos.x - SceneBoxesOut.at(i).Pos.x, 2) + pow(playFuturePos.z - SceneBoxesOut.at(i).Pos.z, 2) < pow(playRad + SceneBoxesOut.at(i).Rad, 2))
	//for (size_t i = 0; i < SceneBoxesIn.size(); i++)
	//{
	//	if (pow(playFuturePos.x - SceneBoxesIn.at(i).Pos.x, 2) + pow(playFuturePos.z - SceneBoxesIn.at(i).Pos.z, 2) < pow(playRad + SceneBoxesIn.at(i).Rad, 2))
	//	{
	//		for (size_t j = 0; j < SceneBoxesOut.size(); j++)
	//		{
	//			if (pow(playFuturePos.x - SceneBoxesOut.at(j).Pos.x, 2) + pow(playFuturePos.z - SceneBoxesOut.at(j).Pos.z, 2) < pow(playRad + SceneBoxesOut.at(j).Rad, 2))
	//			{
	//				hitx = false;
	//				XMFLOAT3 temp =  playFuturePos - SceneBoxesOut.at(j).Pos;
	//				tempX = { temp.x, temp.y, temp.z };
	//				XMVECTOR temp3 = { 0.0f, 1.0f, 0.0f };

	//				tempX = DirectX::XMVector3Normalize(tempX);
	//				tempX = DirectX::XMVector3Cross(tempX, temp3);
	//				tempX = DirectX::XMVector3Normalize(tempX);
	//			}
	//		}

	//	}

	//}
	//for (size_t i = 0; i < SceneBoxesIn.size(); i++)
	//{
	//	if (pow(playFuturePos.x - SceneBoxesIn.at(i).Pos.x, 2) + pow(playFuturePos.z - SceneBoxesIn.at(i).Pos.z, 2) < pow(playRad + SceneBoxesIn.at(i).Rad, 2))
	//	{
	//		for (size_t j = 0; j < SceneBoxesOut.size(); j++)
	//		{
	//			if (pow(playFuturePos.x - SceneBoxesOut.at(j).Pos.x, 2) + pow(playFuturePos.z - SceneBoxesOut.at(j).Pos.z, 2) < pow(playRad + SceneBoxesOut.at(j).Rad, 2))
	//			{
	//				hitz = false;

	//				XMFLOAT3 temp = playFuturePos - SceneBoxesOut.at(j).Pos;
	//				tempZ = { temp.x, temp.y, temp.z };
	//				XMVECTOR temp3 = { 0.0f, 1.0f, 0.0f };

	//				tempZ = DirectX::XMVector3Normalize(tempZ);
	//				tempZ = DirectX::XMVector3Cross(tempZ, temp3);
	//				tempZ = DirectX::XMVector3Normalize(tempZ);
	//			}
	//		}
	//	}
	//}
	//if (hitx == false || hitz == false)
	//{
	//	if (hitx == false)
	//	{
	//		player->position.z -= player->GetVelocity().z;
	//		player->acceleration.z = player->acceleration.z * tempX.m128_f32[2];
	//	}
	//	if (hitz == false)
	//	{
	//		player->position.x -= player->GetVelocity().x;
	//		player->acceleration.x = player->acceleration.x * tempZ.m128_f32[0];
	//	}
	//	return false;
	//}
	//else if (playerPos.x == player->position.x || playerPos.z == player->position.z)
	//{
	//	if (hitx == true)
	//	{
	//		return true;
	//	}
	//	if (hitz == true)
	//	{
	//		return true;
	//	}
	//	return true;
	//}
	//player->position.x -= player->GetVelocity().x;
	//player->position.z -= player->GetVelocity().z;
	//return false;


	for (size_t i = 0; i < SceneBoxesIn.size(); i++)
	{
		if (pow(playFuturePos.x - SceneBoxesIn.at(i).Pos.x, 2)
			+ pow(playFuturePos.z - SceneBoxesIn.at(i).Pos.z, 2)
			< pow(playRad + SceneBoxesIn.at(i).Rad, 2))
		{
			for (size_t i = 0; i < SceneBoxesOut.size(); i++)
			{
				if (pow(playFuturePos.x - SceneBoxesOut.at(i).Pos.x, 2)
					+ pow(playFuturePos.z - SceneBoxesOut.at(i).Pos.z, 2)
					< pow(playRad + SceneBoxesOut.at(i).Rad, 2))
				{
					//XMFLOAT3 temp = SceneBoxesOut.at(i).Pos - playFuturePos;
					//XMVECTOR temp2 = { temp.x, temp.y, temp.z };
					//XMVECTOR temp3 = { 0.0f, 1.0f, 0.0f };

					//temp2 = DirectX::XMVector3Normalize(temp2);
					//temp2 = DirectX::XMVector3Cross(temp2, temp3);
					//temp2 = DirectX::XMVector3Normalize(temp2);

					//player->position.x += tempVel.x * temp2.m128_f32[0];
					//player->position.y = Y_OFFSET;
					//player->position.z += tempVel.z * temp2.m128_f32[2];
					player->position.x -= player->GetVelocity().x;
					//player->position.y = Y_OFFSET;
					player->position.z -= player->GetVelocity().z;
					return false;
				}
			}
			return true;
		}

	}
	player->position.x -= player->GetVelocity().x;
	//player->position.y = Y_OFFSET;
	player->position.z -= player->GetVelocity().z;
	return false;
}
bool Collision::SceneColIn(double deltaTime, EnemyBase* enemy)
{
	for (size_t i = 0; i < SceneBoxesIn.size(); i++)
	{
		if (pow(enemy->GetPosition().x - SceneBoxesIn.at(i).Pos.x, 2)
			+ pow(enemy->GetPosition().z - SceneBoxesIn.at(i).Pos.z, 2)
			< pow(enemy->GetRadius2() + SceneBoxesIn.at(i).Rad, 2))
		{
			for (size_t j = 0; j < SceneBoxesOut.size(); j++)
			{
				if (pow(enemy->GetPosition().x - SceneBoxesOut.at(j).Pos.x, 2)
					+ pow(enemy->GetPosition().z - SceneBoxesOut.at(j).Pos.z, 2)
					< pow(enemy->GetRadius2() + SceneBoxesOut.at(j).Rad, 2))
				{

					Vec3 dir;

					dir.x = SceneBoxesOut.at(j).Pos.x - enemy->position.x;
					dir.z = SceneBoxesOut.at(j).Pos.z - enemy->position.z;

					dir.Normalize();

					enemy->position.x -= dir.x * (float)deltaTime * enemy->movementSpeed;
					enemy->position.z -= dir.z * (float)deltaTime * enemy->movementSpeed;
					return false;
				}
			}
			return true;
		}

	}
	//Vec3 dir;

	//dir.x = 0 - enemy->position.x;
	//dir.z = 0 - enemy->position.z;

	//{ 82.944f, 0.0f, 63.105f + GetSpawnPosAdd() };

	enemy->position.x = 0;
	enemy->position.z = 0;
	return false;
}
bool Collision::PlayerDistanceCollision(EnemyBase* enemy)
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

bool Collision::ProjectileEnemyCollision(Projectile* projectile, EnemyBase* enemy)
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

bool Collision::EnemyCollision(EnemyBase* enemy, EnemyBase* enemys)
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

bool Collision::TrapandEnemyLottery(EnemyBase* enemys)
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

bool Collision::WeaponPickupCollision(Pickup* pickup)
{
	
	if (pickup->GetIsActive())
	{
		XMFLOAT3 pickupPos = pickup->GetPosition();
		float pickupRad = pickup->GetRadius();

		XMFLOAT3 playerPos = this->player->position;
		float playerRad = this->player->GetRadius();

		if (pow(pickupPos.x - playerPos.x, 2)
			+ pow(pickupPos.z - playerPos.z, 2)
			< pow(pickupRad + playerRad, 2))
		{
			return true;
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



