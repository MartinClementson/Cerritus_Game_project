#pragma once
#include "../ObjectNode.h"
#include "../../../Structs/DataTypes.h"


class Mesh : public ObjectNode
{
	bool	    hasSkeleton			= false;
	Vertex*		vertices			= nullptr;
	AnimVert*	animVertices		= nullptr;


	ID3D11Buffer* vertexBuffer		= nullptr;
	ID3D11Buffer* indexBuffer		= nullptr;
	unsigned int  vertCount			= 0;
	UINT			indexCount		= 0;

	unsigned int  skeletonID		= 0;
	int  materialID		= 0;

public:
	Mesh(bool hasSkeleton, unsigned int skeletonID, unsigned int materialID);
	Mesh();
	~Mesh();

	void Initialize(ID3D11Device *gDevice, ID3D11DeviceContext* gDeviceContext);
	void Release();

	void GetMeshRenderInfo(RenderInstructions* toRender);

	int GetMaterialID() { return this->materialID; }
	void SetMaterialID(int id) { this->materialID = id; }
	void CreateVertexBuffer(Vertex* vertices, unsigned int amount);
	void CreateVertexBuffer(AnimVert* vertices, unsigned int amount);

	void CreateIndexBuffer(UINT* indices,unsigned int amount);
};

