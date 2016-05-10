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

	Vertex* sceneVerts				= nullptr;
	UINT* sceneIndex				= nullptr;
	bool isScene					= false;
public:
	Mesh(bool hasSkeleton, unsigned int skeletonID, unsigned int materialID);
	Mesh();
	~Mesh();

	void Initialize(ID3D11Device *gDevice, ID3D11DeviceContext* gDeviceContext);
	void Release();

	unsigned int GetVertexCount() { return this->vertCount; };
	UINT GetIndexCount() { return this->indexCount; };

	void GetMeshRenderInfo(RenderInstructions* toRender);

	bool GetIsScene() { return this->isScene; };
	Vertex* GetVertices() { return this->sceneVerts; };
	UINT* GetIndices() { return this->sceneIndex; };
	int GetMaterialID() { return this->materialID; };
	void SetMaterialID(int id) { this->materialID = id; };
	void CreateVertexBuffer(Vertex* vertices, unsigned int amount, bool isScene);
	void CreateVertexBuffer(AnimVert* vertices, unsigned int amount);
	void setSceneVertexBuffer(unsigned int amount, ID3D11Buffer* vertexBuffer);
	void setSceneIndexBuffer(UINT amount, ID3D11Buffer* indexBuffer);

	void CreateIndexBuffer(UINT* indices,unsigned int amount, bool isScene);
};

