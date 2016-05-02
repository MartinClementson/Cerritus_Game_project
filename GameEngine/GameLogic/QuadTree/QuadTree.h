#include "../../Source/LibIncluder.h"
#include "../Character/Enemy/Enemy.h"
#include "../Character/Player/Player.h"
#include "../Character/ProjectileSystem/Projectile/Projectile.h"
#include "../Scene/Trap/BearTrap/BearTrap.h"
#include "../Scene/Trap/FireTrap/FireTrap.h"

using namespace DirectX;
using namespace std;


#pragma once
class QuadTree
{
public:
	QuadTree(int level, XMFLOAT3 size);
	virtual ~QuadTree();
private:
	int MAX_OBJECTS = 10;
	int MAX_LEVELS = 5;
	
	int level;
	vector<Character*> characters;
	/*std::vector<Enemy*> enemies;
	std::vector<Player*> player;*/
	/*std::vector<Projectile*> projectiles;
	std::vector<BearTrap*> bearTrap;
	std::vector<FireTrap*> enemies;*/
	XMFLOAT3 size;
	std::vector<QuadTree*> nodes;
	void split();
	

	QuadTree();
};

