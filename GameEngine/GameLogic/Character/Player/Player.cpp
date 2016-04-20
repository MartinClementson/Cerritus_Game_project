#include "Player.h"



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

	projectileSystem->Initialize();

	this->position = XMFLOAT3(0.0f, 0.0f, 1.0f);
	this->rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);

}

void Player::Release()
{
}

void Player::Update(double deltaTime)
{
	renderInfo = { position,rotation };

	projectileSystem->UpdateProjectile(deltaTime);
}

void Player::Render()
{
	
	graphics->QueueRender(&renderInfo);
}

void Player::Move(MovementDirection dir, double deltaTime)
{
	if (dir == UP)
	{
		position.z += position.z + 1 * (float)deltaTime;
	}
	else if (dir == DOWN)
	{
		position.z += position.z - 1 * (float)deltaTime;
	}
	else if (dir == LEFT)
	{
		position.x += position.x + 1 * (float)deltaTime;
	}
	else if (dir == RIGHT)
	{
		position.x += position.x - 1 * (float)deltaTime;
	}
}

void Player::Shoot(InputKeys input, double deltaTime)
{
	if (input == MOUSE_LEFT)
	{
		projectileSystem->FireProjectile(this->position, this->rotation);
		
	}
	if (input == KEY_LEFT)
	{
		projectileSystem->FireProjectile(this->position, this->rotation);
	}


}
