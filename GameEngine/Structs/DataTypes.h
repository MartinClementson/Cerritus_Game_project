#pragma once


struct Float2
{
	float x;
	float y;

	Float2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
	Float2() {};
};

struct Float3
{
	float x;
	float y;
	float z;

	Float3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Float3() {};
};

struct Float4
{
	float x;
	float y;
	float z;
	float w;

	Float4(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}
	Float4() {};
};

struct INT4
{
	int x;
	int y;
	int z;
	int w;

	INT4(int x, int y, int z, int w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}
	INT4() {};
};

struct UINT4
{
	unsigned int x;
	unsigned y;
	unsigned z;
	unsigned w;

	UINT4(unsigned x, unsigned y, unsigned z, unsigned w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}
	UINT4() {};
};


struct Double3
{
	double x;
	double y;
	double z;

	Double3() {};

	Double3(double x, double y, double z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
};




struct Vertex
{
	Float3 position;
	Float3 normal;
	Float2 uv;
	Float2 biTangent;
	Float2 tangent;

	Vertex(Float3 pos, Float3 normal, Float2 uv, Float2 tangent, Float2 biTangent)
	{
		this->position.x = pos.x;
		this->position.y = pos.y;
		this->position.z = pos.z;

		this->normal.x = normal.x;
		this->normal.y = normal.y;
		this->normal.z = normal.z;

		this->uv.x = uv.x;
		this->uv.y = uv.y;

		this->tangent.x = tangent.x;
		this->tangent.y = tangent.y;

		this->biTangent.x = biTangent.x;
		this->biTangent.y = biTangent.y;

	}
	Vertex() {};

};

struct InstancedData
{
	InstancedData() { ZeroMemory(this, sizeof(this)); };
	DirectX::XMFLOAT4X4 worldMatrix;
	unsigned int glow = 0;
};

struct BillboardData
{
	DirectX::XMFLOAT3 worldPos  = DirectX::XMFLOAT3(0.0f,0.0f,0.0f);
	DirectX::XMFLOAT3 direction = DirectX::XMFLOAT3(1.0f, 0.0f, 0.0f);
	DirectX::XMFLOAT3 color		= DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	float height	  = 1.0f;
	float width		  = 1.0f;
	unsigned int glow = 0;
};

struct AnimVert
{
	Float3 position;
	Float3 normal;
	Float2 uv;
	Float2 biTangent;
	Float2 tangent;

	Float4 weights;
	UINT4 jointID;

	AnimVert(Float3 pos, Float3 normal, Float2 uv, Float2 tangent, Float2 biTangent, Float4 weights, UINT4 jointID)
	{
		this->position.x = pos.x;
		this->position.y = pos.y;
		this->position.z = pos.z;

		this->normal.x = normal.x;
		this->normal.y = normal.y;
		this->normal.z = normal.z;

		this->uv.x = uv.x;
		this->uv.y = uv.y;

		this->biTangent.x = biTangent.x;
		this->biTangent.y = biTangent.y;

		this->tangent.x = tangent.x;
		this->tangent.y = tangent.y;

		this->weights.x = weights.x;
		this->weights.y = weights.y;
		this->weights.z = weights.z;
		this->weights.w = weights.w;

		this->jointID.x = jointID.x;
		this->jointID.y = jointID.y;
		this->jointID.z = jointID.z;
		this->jointID.w = jointID.w;
	}
	AnimVert() {};

};


struct ProjectileStruct
{
	Float3 position;
	Float3 rotation;
};

struct Material
{
	std::string materialName;
	int materialID;
	Float3 diffuseValue;
	Float3 specularValue;

	//if the id is -1, the material doesn't have a texture
	int diffuse_ID;
	int normal_ID;
	int specular_ID;
	int glow_ID;
};
struct importedMaterial
{
	std::string materialName;
	int materialID;
	Float3 diffuseValue;
	Float3 specularValue;

	std::string diffuseTex;
	std::string normalTex;
	std::string specularTex;
	std::string glowTex;
};

struct NodeType
{
	Float2 position;
	float width;
	unsigned int materialID;
	bool isAnimated;
	unsigned int triangleCount;
	ID3D11Buffer *vertexBuffer;
	ID3D11Buffer *indexBuffer;
	UINT VertexCount;
	UINT IndexCount;
	NodeType* nodes[4];
};