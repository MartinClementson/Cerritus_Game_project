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

	this->position		 = XMFLOAT3(-5.0f, 0.0f, -5.0f);
	this->rotation		 = XMFLOAT3(0.0f, 0.0f, 0.0f);
	this->movementSpeed  = 50.0f;

	radius = 1.0f;

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
	if (dir == UP)
	{
		position.z += movementSpeed * (float)deltaTime;
	}
	else if (dir == DOWN)
	{
		position.z -= movementSpeed * (float)deltaTime;
	}
	else if (dir == LEFT)
	{
		position.x -= movementSpeed * (float)deltaTime;
	}
	else if (dir == RIGHT)
	{
		position.x += movementSpeed * (float)deltaTime;
	}
}

void Player::Shoot(InputKeys input, double deltaTime)
{
	/*if (input == MOUSE_LEFT)
	{
		projectileSystem->FireProjectile(this->position, this->rotation);
		
	}*/
	if (input == KEY_SPACE)
	{
		projectileSystem->FireProjectile(this->position, direction);
	}


}
