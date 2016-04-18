#pragma once
#include "../Source/LibIncluder.h"
#include "../Enumerations/Enumerations.h"

using namespace DirectX;

struct RenderInstructions
{
	/*
	This struct only holds pointers to information
	When we want to render something. We send a set of instructions (see structs below) to the resource handler.
	Then the resource handler fills this struct with the information of the mesh that is to be rendered.
	Then this struct is returned to the Renderer that proceeds to update the buffers, resources and finally draws the geometry.

	*/

	bool* isAnimated						 = nullptr; //this is important to make sure we use the right vert struct

	XMFLOAT4X4* worldMatrix					 = nullptr;
	XMFLOAT4X4* normalWorld					 = nullptr;
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

	MeshEnum object;
	Shaders shader;		//these are enum
};


struct RenderInfoUI {
	XMFLOAT3 position;
	XMFLOAT3 rotation;

	// Objects object
	// Shader shader		//these are enum
};

struct RenderInfoEnemy {
	XMFLOAT3 position;
	XMFLOAT3 rotation;

	// Objects object
	// Shader shader		//these are enum
};

struct RenderInfoChar {
	XMFLOAT3 position;
	XMFLOAT3 rotation;

	// Objects object
	// Shader shader		//these are enum
};

struct RenderInfoTrap {
	XMFLOAT3 position;
	XMFLOAT3 rotation;

	// Objects object
	// Shader shader		//these are enum
};