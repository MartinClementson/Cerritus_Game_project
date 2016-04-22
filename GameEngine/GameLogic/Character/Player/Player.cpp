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





Player::Player()
{
	this->projectileSystem = new ProjectileSystem;

}


Player::~Player()
{

	delete this->projectileSystem;

}

void Player::Initialize()
{
	graphics			 = Graphics::GetInstance();

	this->position		 = XMFLOAT3(-5.0f, 0.0f, -5.0f);
	this->rotation		 = XMFLOAT3(0.0f, 0.0f, 0.0f);


	radius				 = 1.0f;

	projectileSystem->Initialize();
}

void Player::Release()
{
	projectileSystem->Release();
}

void Player::Update(double deltaTime, XMFLOAT3 direction)
{
	this->direction	 = direction;
	renderInfo		 = { position,rotation };

	

	velocity.x		 += acceleration.x * (float)deltaTime - velocity.x * fallOfFactor * (float)deltaTime;
	velocity.y		  = 0.0f;
	velocity.z		 += acceleration.z * (float)deltaTime - velocity.z * fallOfFactor * (float)deltaTime;
	

	float currentVelo = velocity.Length();

	if (currentVelo > VELOCITY_MAX)
	{

		Vec3 normalizer			= velocity.Normalize();
		normalizer				= normalizer * VELOCITY_MAX;
		velocity				= normalizer;
	}

	if (currentVelo > 0.05f)
	{
		position.x				+= velocity.x;
		position.y				 = 0.0f;
		position.z				+= velocity.z;


	}


	acceleration				 = Vec3(0.0f, 0.0f, 0.0f); //reset acceleration for next frame
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
			acceleration.z = maxAcceleration;
		}

		if (dir[i] == DOWN)
		{
			acceleration.z = -maxAcceleration;
		}
		if (dir[i] == LEFT)
		{
			acceleration.x = -maxAcceleration;
		}
		if (dir[i] == RIGHT)
		{
			acceleration.x = maxAcceleration;
		}

		float len = acceleration.Length();

		if (len > maxAcceleration)
		{
			Vec3 normalizer	  = acceleration.Normalize();
			normalizer		  = normalizer * maxAcceleration;
			acceleration	  = normalizer;



		}
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


}
