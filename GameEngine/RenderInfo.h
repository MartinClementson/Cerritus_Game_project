#pragma once
#include "LibIncluder.h"

using namespace DirectX;

struct RenderInstructions
{
	/*
	This struct only holds pointers to information
	When we want to render something. We send a set of instructions (see structs below) to the resource handler.
	Then the resource handler fills this struct with the information of the mesh that is to be rendered.
	Then this struct is returned to the Renderer that proceeds to update the buffers, resources and finally draws the geometry.

	*/

	bool* isAnimated					 = nullptr; //this is important to make sure we use the right vert struct

	XMFLOAT4X4* worldMatrix				 = nullptr;
	XMFLOAT4X4* normalWorld				 = nullptr;
	ID3D11Buffer* vertexBuffer			 = nullptr;
	unsigned int* vertexCount			 = 0;

	ID3D11Buffer* indexBuffer			 = nullptr;
	unsigned int* indexCount			 = 0;

	ID3D11ShaderResourceView* diffuse	 = nullptr;
	ID3D11ShaderResourceView* normal	 = nullptr;
	ID3D11ShaderResourceView* specular	 = nullptr;
	ID3D11ShaderResourceView* glow		 = nullptr;
};

struct RenderInfoObject {
	XMFLOAT3 position;
	XMFLOAT3 rotation;

	// Objects object
	// Shader shader		//these are enum
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