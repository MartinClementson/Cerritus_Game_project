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
	graphics = Graphics::GetInstance();

	this->position		 = XMFLOAT3(0.0f, 0.0f, 1.0f);
	this->rotation		 = XMFLOAT3(0.0f, 0.0f, 0.0f);
	this->movementSpeed  = 50.0f;

	projectileSystem->Initialize();
}

void Player::Release()
{
	projectileSystem->Release();
}

void Player::Update(double deltaTime, XMFLOAT3 direction)
{
	this->direction = direction;
	renderInfo = { position,rotation };

	projectileSystem->UpdateProjectiles(deltaTime);
}

void Player::Render()
{
	graphics->QueueRender(&renderInfo);
	projectileSystem->Render();
}

void Player::Move(MovementDirection dir, double deltaTime)
{
	XMFLOAT3 moveAmount = { 0.0f, 0.0f, 0.0f };

	if (dir == UP)
	{
		moveAmount.z += movementSpeed ;
	}

	 if (dir == DOWN)
	{
		moveAmount.z -= movementSpeed ;
	}
	 if (dir == LEFT)
	{
		moveAmount.x -= movementSpeed ;
	}
	 if (dir == RIGHT)
	{
		moveAmount.x += movementSpeed ;
	}
	 position = position + (moveAmount * (float)deltaTime);
}

void Player::Shoot(InputKeys input, double deltaTime)
{
	/*if (input == MOUSE_LEFT)
	{
		projectileSystem->FireProjectile(this->position, this->rotation);
		
	}*/
	if (input == MOUSE_LEFT)
	{
		projectileSystem->FireProjectile(this->position, direction);
	}
	else if (input == KEY_SPACE)
	{
		projectileSystem->FireProjectile(this->position, direction);
	}


}
