#pragma once
enum EnemyAnimations
{
	WALK,
	DIE,
	JUMP,
	ATTACK
};

enum PlayerAnimation
{
	WALK,
	DIE,
	SHOOT
};

enum Meshes
{
	MAIN_CHARACTER,
	ENEMY_1,
	PROJECTILE_1,
	TRAP_BEAR,
	TRAP_FIRE
};

enum UITextures
{
	HEALTHBAR,
	WAVECOUNTER
};

enum LightType
{
	POINTLIGHT,
	AREALIGHT
};

enum Shaders
{
	PHONG_SHADER,
	PARTICLE_SHADER,
	BILLBOARD_SHADER,
	UI_SHADER,
	ANIMATION_SHADER
};

enum TrapState
{
	IDLE,
	ACTIVE,
	INACTIVE
};

enum EnemyState
{
	IDLE,
	ATTACK,
	DEATH
};

enum States
{
	MENU,
	GAME,
	GAMEOVER
};

enum InputKeys
{
	KEY_W,
	KEY_A,
	KEY_S,
	KEY_D,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_UP,
	KEY_DOWN,
	KEY_SPACE,
	KEY_ENTER,

	MOUSE_RIGHT,
	MOUSE_LEFT
};

enum TextureType
{
	DIFFUSE,
	SPECULAR,
	GLOW,
	NORMAL
};