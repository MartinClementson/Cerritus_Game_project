#pragma once
#include "../Source/LibIncluder.h"

#include "../Enumerations/Enumerations.h"

#include "ConstantBufferStruct.h"


using namespace DirectX;

struct RenderInstructions
{
	/*
	This struct only holds pointers to information
	When we want to render something. We send a set of instructions (see structs below) to the resource handler.
	Then the resource handler fills this struct with the information of the mesh that is to be rendered.
	Then this struct is returned to the Renderer that proceeds to update the buffers, resources and finally draws the geometry.

	*/
	unsigned int materialID;

	bool* isAnimated						 = nullptr; //this is important to make sure we use the right vert struct

	WorldMatrix worldBuffer;
	
	ID3D11Buffer* vertexBuffer				 = nullptr;
	UINT* vertexCount						 = 0;

	ID3D11Buffer* indexBuffer				 = nullptr;
	UINT* indexCount						 = 0;

	ID3D11ShaderResourceView* diffuseMap	 = nullptr;
	ID3D11ShaderResourceView* normalMap		 = nullptr;
	ID3D11ShaderResourceView* specularMap	 = nullptr;
	ID3D11ShaderResourceView* glowMap		 = nullptr;
};

struct RenderInfoObject {
	XMFLOAT3 position;
	XMFLOAT3 rotation;
	XMFLOAT3 direction;
	MeshEnum object;
	bool render = true;
	float radius;
};


struct RenderInfoUI {
	XMFLOAT3 position;
	XMFLOAT3 rotation;
	MeshEnum object;
	Shaders shader;	//these are enum
	float radius;
};

struct RenderInfoEnemy {
	XMFLOAT3 position;
	XMFLOAT3 rotation;
	MeshEnum object;
	bool render				  = true;
	bool showHealthBar		  = true;
	float normalizedHealthVal = 0.3f; //this value is calculated  with currentHealth/maxHealth. This controls the size and color of the healthbar
	float radius;

	//EnemyAnimations enemyAnim;	//these are enum
};

struct RenderInfoChar {
	XMFLOAT3 position;
	XMFLOAT3 rotation;
	float radius;
	//MeshEnum object;
	//Shaders shader;
	//PlayerAnimation playerAnim; //these are enum
};

struct RenderInfoTrap {
	XMFLOAT3 position;
	XMFLOAT3 rotation;
	MeshEnum object;
	bool render = true;
	float radius;
	//Shaders shader;
	//TrapAnimations trapAnim;*/ //these are enum
};
struct RenderInfoProjectile {
	XMFLOAT3 origin;
	XMFLOAT3 direction;
	float radius;

};