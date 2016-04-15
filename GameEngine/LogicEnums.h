#pragma once

#pragma region Animations

#pragma region EnemyAnimation
enum EnemyAnimations
{
	WALK,
	DIE,
	JUMP,
	ATTACK
};
#pragma endregion

#pragma region PlayerAnimation
enum PlayerAnimation
{
	WALK,
	DIE,
	SHOOT
};
#pragma endregion

#pragma endregion

#pragma region Meshes

enum Meshes
{
	MAIN_CHARACTER,
	ENEMY_1,
	PROJECTILE_1,
	TRAP_BEAR,
	TRAP_FIRE
};

#pragma endregion

#pragma region UI

enum UITextures
{
	HEALTHBAR,
	WAVECOUNTER
};

#pragma endregion

#pragma region Lights

enum LightType
{
	POINTLIGHT,
	AREALIGHT
};

#pragma endregion

#pragma region Shaders

enum Shaders
{
	PHONG_SHADER,
	PARTICLE_SHADER,
	BILLBOARD_SHADER,
	UI_SHADER,
	ANIMATION_SHADER
};

#pragma endregion

#pragma region States

#pragma region TrapState

enum TrapState
{
	IDLE,
	ACTIVE,
	INACTIVE
};

#pragma endregion

#pragma region EnemyState

enum EnemyState
{
	IDLE,
	ATTACK,
	DEATH
};

#pragma endregion

#pragma region MainState

enum MainStates
{
	MENU,
	GAME,
	GAMEOVER
};

#pragma endregion

#pragma endregion

#pragma region Input

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

#pragma endregion

#pragma region Texture

enum TextureType
{
	DIFFUSE,
	SPECULAR,
	GLOW,
	NORMAL
};

#pragma endregion