#pragma once
#include "../ObjectNode.h"
#include "../../../Structs/DataTypes.h"

class Mesh : public ObjectNode
{
	bool	        hasSkeleton			= false;
	Vertex*		    vertices			= nullptr;
	AnimVert*	    animVertices		= nullptr;

	bool			isAnimated			= false;

	bool	        isBlendShape		= false;
	BlendShapeVert* blendVerts		    = nullptr;

	ID3D11Buffer*   vertexBuffer		= nullptr;
	ID3D11Buffer*   indexBuffer		    = nullptr;
	unsigned int    vertCount			= 0;
	UINT			indexCount		    = 0;
									    
	unsigned int  skeletonID		    = 0;
	int  materialID					    = 0;

	Vertex* sceneVerts				= nullptr;
	UINT* sceneIndex				= nullptr;
	bool isScene					= false;
public:
	unsigned int	animationCount		= 0;
	std::vector<AnimationInfo> animations;
	Mesh(bool hasSkeleton, unsigned int skeletonID, unsigned int materialID);
	Mesh();
	Mesh(ID3D11Device *gDevice, ID3D11DeviceContext* gDeviceContext);
	~Mesh();

	void Initialize(ID3D11Device *gDevice, ID3D11DeviceContext* gDeviceContext);
	void Release();

	unsigned int GetVertexCount() { return this->vertCount; };
	UINT GetIndexCount() { return this->indexCount; };

	void GetMeshRenderInfo(RenderInstructions* toRender);
	BlendShapeBuffer GetMeshBlendShape();

	int GetMaterialID()		   { return this->materialID; }
	void SetMaterialID(int id) { this->materialID = id;	  }
	
	void CreateVertexBuffer(AnimVert* vertices,		unsigned int amount);
	void CreateBlendShape (BlendShapeVert* vertices, unsigned int amount);
	void CreateAnimatedMesh(Vertex * vertices, unsigned int vertAmount, std::vector<AnimationInfo>* animations);
	unsigned int GetVertCount() { return this->vertCount; };

	bool GetIsScene() { return this->isScene; };
	Vertex* GetVertices() { return this->sceneVerts; };
	UINT* GetIndices() { return this->sceneIndex; };

	void CreateVertexBuffer(Vertex* vertices, unsigned int amount, bool isScene);


	void CreateIndexBuffer(UINT* indices,unsigned int amount, bool isScene);
};

