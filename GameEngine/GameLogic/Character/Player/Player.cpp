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
	this->movementSpeed = 100.0f;


}

void Player::Release()
{
	projectileSystem->Release();
}

void Player::Update(double deltaTime)
{
	renderInfo = { position,rotation };

	projectileSystem->UpdateProjectile(deltaTime);
}

void Player::Render()
{
	graphics->QueueRender(&renderInfo);
	//projectileSystem->Render();
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
	if (input == KEY_LEFT)
	{
		projectileSystem->FireProjectile(this->position, this->rotation);
	}


}
