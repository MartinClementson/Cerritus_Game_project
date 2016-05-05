#pragma once

#pragma region Animations

#pragma region EnemyAnimation
enum EnemyAnimations
{
	ENEMY_WALK,
	ENEMY_DIE,
	ENEMY_JUMP,
	ENEMY_ATTACK
};
#pragma endregion

#pragma region PlayerAnimation
enum PlayerAnimation
{
	PLAYER_WALK,
	PLAYER_DIE,
	PLAYER_SHOOT
};
#pragma endregion

enum TrapAnimations
{
	TRAP_ACTIVATE,
	TRAP_IDLE,
	TRAP_USED
};

#pragma endregion

#pragma region Meshes

enum MeshEnum
{
	MAIN_CHARACTER,
	ENEMY_1,
	PROJECTILE_1,
	TRAP_BEAR,
	TRAP_FIRE,
	LEVEL_1,
	LEVEL_2,
	LEVEL_3,
	LEVEL_4
};

#pragma endregion

enum CharacterType
{
	PLAYER,
	SLOW_ENEMY,
	FAST_ENEMY,
	HEALER
};

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
	POINT_LIGHT,
	SPOT_LIGHT,
	DIRECTIONAL_LIGHT
};

#pragma endregion

#pragma region Shaders

enum Shaders
{
	FINAL_SHADER,
	PARTICLE_SHADER,
	BILLBOARD_SHADER,
	UI_SHADER,
	ANIMATION_SHADER,
	GBUFFER_SHADER,
	SHADOW_SHADER
};

#pragma endregion

#pragma region States

#pragma region TrapState

enum TrapState
{
	TRAP_IDLE_STATE,
	TRAP_ACTIVE_STATE,
	TRAP_INACTIVE_STATE
};

#pragma endregion

#pragma region EnemyState

enum EnemyState
{
	ENEMY_IDLE_STATE,
	ENEMY_ATTACK_STATE,
	ENEMY_DEATH_STATE,
	ENEMY_HEAL_STATE
};

#pragma endregion

#pragma region MainState

enum MainStates
{
	MAIN_MENU_STATE,
	MAIN_GAME_STATE,
	MAIN_GAMEOVER_STATE
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
	KEY_ESC,
	KEY_Z,
	KEY_X,
	KEY_C,

	MOUSE_RIGHT,
	MOUSE_LEFT
};

#pragma region MovementDirection

enum MovementDirection 
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

#pragma endregion

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

#pragma region Particle

enum ParticleType
{
	FIRE,
	RAIN,
};

#pragma endregion


enum UpgradeType
{
	ONE_SHOT,
	TWO_SHOT,
	THREE_SHOT,

};

enum GbufferTextures
{
	G_DIFFUSE,
	G_SPECULAR,
	G_NORMAL,
	G_DEPTH,
	G_SHADOW

};