#include "Player.h"

inline DirectX::XMFLOAT3 operator+(DirectX::XMFLOAT3 a, DirectX::XMFLOAT3 b) {
	DirectX::XMFLOAT3 result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;

	return result;
}

inline DirectX::XMFLOAT3 operator*(DirectX::XMFLOAT3 a, float b) {
	DirectX::XMFLOAT3 result;

	result.x = a.x * b;
	result.y = a.y * b;
	result.z = a.z * b;

	return result;
}

inline DirectX::XMFLOAT3 operator+(DirectX::XMFLOAT3 a, Vec3 b) {
	DirectX::XMFLOAT3 result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;

	return result;
}

inline float get_degrees(float radian)
{

	return (radian * 180) / XM_PI;
}

Player::Player()
{
	this->projectileSystem = new ProjectileSystem;

}

Player::~Player()
{

	delete this->projectileSystem;

}





void Player::Initialize(AudioManager* audioManager)
{
	
	graphics			 = Graphics::GetInstance();

	this->position		 = XMFLOAT3(-5.0f, Y_OFFSET, -5.0f);
	this->rotation		 = XMFLOAT3(0.0f, 0.0f, 0.0f);
	VelocityMax = 4.0f;
	slowTimer = 0;

	points = 0;
	multiplier = 1;
	radius = 2.0f;
	radius2 = 2.0f;
	fall = false;
	thrust = true;

	DoT = 0.0f;
	DoTDur = 0.0f;
	health = 100.0f;
	maxHealth = health;
	projectileSystem->Initialize(audioManager);
	SetUpgrade(UpgradeType::ONE_SHOT);
	
}

void Player::Release()
{
	projectileSystem->Release();
}

void Player::Update(double deltaTime, XMFLOAT3 direction)
{


	if (VelocityMax == 0.2f)
	{
		slowTimer += (float)deltaTime;

	}
	if (slowTimer > 2.0f)
	{
		VelocityMax = 4.0f;
		slowTimer = 0.0f;
	}

	if (DoT != 0)
	{
		DoTDur += (float)deltaTime;
	}
	if (DoTDur > 1)
	{
		DoT = 0.0f;
		DoTDur = 0.0f;
	}

	health -= DoT;
	if (health <= 0)
	{

		/*MessageBox(0, L"You Died",
		L"Continue", MB_OK);*/
		//health = 100.0f;
	}

	grav = position.y;

	if (thrust)
	{
		acceleration.y += +maxAcceleration *grav *deltaTime * 0.6;
		if (position.y > 1.2f)
		{
			thrust = false;
		}
	}
	if (!thrust && !fall)
	{
		if (velocity.y < 0.01 && position.y > 1.2f)
		{
			fall = true;
		}
		else if (velocity.y < 0.01 && position.y < 1.0f)
		{
			thrust = true;
		}
	}
	if(fall)
	{
		acceleration.y += -maxAcceleration * grav*deltaTime * 0.6;
		if (position.y < 1.0f)
		{
			fall = false;
		}
	}


	

	this->direction	 = direction;
	

#pragma region Calculate movement

	velocity.x		 += acceleration.x * (float)deltaTime - velocity.x * fallOfFactor * (float)deltaTime;
	velocity.y		 += acceleration.y * (float)deltaTime - velocity.y * (fallOfFactor/2) * (float)deltaTime;
	velocity.z		 += acceleration.z * (float)deltaTime - velocity.z * fallOfFactor * (float)deltaTime;
	

	float currentVelo = velocity.Length();

	if (currentVelo > VelocityMax)
	{

		Vec3 normalizer			= velocity.Normalize();
		normalizer				= normalizer * VelocityMax;
		velocity				= normalizer;
	}

	if (currentVelo > 0.0f)
	{
		position.x				+= velocity.x;
		position.y				+= velocity.y;
		position.z				+= velocity.z;


	}


	acceleration				 = Vec3(0.0f, 0.0f, 0.0f); //reset acceleration for next frame
#pragma endregion
	


#pragma region Calculate  rotation of mesh

	XMVECTOR mouseDirection = XMVectorSet(direction.x, 0.0f, direction.z, 0.0f);
	XMVECTOR meshDirection = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);


	//Calculate angle between meshDir and shotDir
	float cosAngle = XMVector3Dot(mouseDirection, meshDirection).m128_f32[0];
	float angle = acos(cosAngle);
	float degrees = get_degrees(angle);
	////////////////////////////////////////////////////

	if (direction.x < 0)
		degrees = -degrees;

	rotation.y = degrees;

	renderInfo = { position,rotation };
#pragma endregion
	

projectileSystem->UpdateProjectiles(deltaTime);
}

void Player::Render()
{
	graphics->QueueRender(&renderInfo);
	projectileSystem->Render();
}

void Player::Move(MovementDirection* dir, int keyAmount, double deltaTime)
{
	
	for (int i = 0; i < keyAmount; i++)
	{
		if (dir[i] == UP)
		{
			acceleration.z = maxAcceleration / keyAmount;
		}

		if (dir[i] == DOWN)
		{
			acceleration.z = -maxAcceleration / keyAmount;
		}
		
		if (dir[i] == LEFT)
		{
			acceleration.x = -maxAcceleration / keyAmount;
		}
		if (dir[i] == RIGHT)
		{
			acceleration.x = maxAcceleration / keyAmount;
		}


	}


		float len = acceleration.Length();
		if (len > maxAcceleration)
		{
			Vec3 normalizer	  = acceleration.Normalize();
			normalizer		  = normalizer * maxAcceleration;
			acceleration	  = normalizer;
		}


}

void Player::Shoot(InputKeys input, double deltaTime)
{
	
	if (input == MOUSE_LEFT)
	{
		projectileSystem->FireProjectile(this->position, direction);
	}
	else if (input == KEY_SPACE)
	{
		projectileSystem->FireProjectile(this->position, direction);
	}
	else if (input == KEY_Z)
	{
		SetUpgrade(UpgradeType::ONE_SHOT);
	}
	else if (input == KEY_X)
	{
		SetUpgrade(UpgradeType::TWO_SHOT);
	}
	else if (input == KEY_C)
	{
		SetUpgrade(UpgradeType::THREE_SHOT);
	}
}

float Player::GetHealth()
{
	return this->health;
}

void Player::SetHealth(float health)
{
	this->health = health;
}

void Player::SetPoints(float points)
{
	this->points = points;
}

float Player::GetPoints()
{
	return this->points;
}

void Player::SetMulti(float multi)
{
	this->multiplier = multi;
}

float Player::GetMulti()
{
	return this->multiplier;
}

UpgradeType Player::GetUpgrade()
{
	return upgrade;
}

void Player::SetUpgrade(UpgradeType upgrade)
{
	this->upgrade = upgrade;
	projectileSystem->SetUpgrade(upgrade);
}

void Player::UpgradeWeapon()
{
	if (GetUpgrade() == UpgradeType::ONE_SHOT)
	{
		SetUpgrade(UpgradeType::TWO_SHOT);
	}
	else if(GetUpgrade() == UpgradeType::TWO_SHOT)
	{
		SetUpgrade(UpgradeType::THREE_SHOT);
	}
	else if (GetUpgrade() == UpgradeType::THREE_SHOT)
	{

	}
}

void Player::DowngradeWeapon()
{
	if (GetUpgrade() == UpgradeType::ONE_SHOT)
	{
		
	}
	else if (GetUpgrade() == UpgradeType::TWO_SHOT)
	{
		SetUpgrade(UpgradeType::ONE_SHOT);
		
	}
	else if (GetUpgrade() == UpgradeType::THREE_SHOT)
	{
		SetUpgrade(UpgradeType::TWO_SHOT);
	}
}

float Player::GetMaxHealth()
{
	return this->maxHealth;
}