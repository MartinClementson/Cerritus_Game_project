#pragma once
#include "../LibIncluder.h"
#include "../Constants.h"
#include "../../Structs/DataTypes.h"
#include "../../Structs/RenderInfo.h"
#include "../Camera/Frustum/Frustum.h"
#include "../Mesh/Mesh.h"
using namespace DirectX;
//GLOBAL
const int maxTriangles = 2000;

class QuadTree
{
private:
	struct NodeType
	{
		Float2 position;
		float width;
		unsigned int triangleCount;
		ID3D11Buffer *vertexBuffer;
		ID3D11Buffer *indexBuffer;
		NodeType* nodes[4];
	};

	ID3D11DeviceContext* gDeviceContext	 = nullptr;		//Devices
	ID3D11Device* gDevice				 = nullptr;		//Devices

	ID3D11Buffer* worldBuffer			 = nullptr;		//ptr to engine world constantbuffer

	XMFLOAT4X4 worldMatrix;
	XMFLOAT4X4 normalWorld;								//might be depricated

	unsigned int			m_triangleCount;
	unsigned int			m_drawCount;
	std::vector<Vertex*>*	m_vertexList;
	std::vector<UINT*>*		m_indexList;
	std::vector<Vertex>*	vertextest;
	std::vector<UINT>*		indextest;
	NodeType*				m_parentNode;

	Vertex* combinedvertices = nullptr;
	UINT* combinedindices = nullptr;

	unsigned int vertexCount;
	UINT indexCount;

	void ReleaseNode(NodeType *node);
	void RenderNode(NodeType *node, ID3D11DeviceContext *gDeviceContext, Frustum* frustum, ID3D11Buffer* worldBuffer);
	void CalculateMeshDimensions(int count, Float2 & position, float &meshWidth);
	void CreateTreeNode(NodeType *parent, Float2 position, float width, ID3D11Device *gDevice, std::vector<Mesh>* terrain);
	int	 CountTriangles(Float2 position, float width);
	bool IsTriangleContained(int index, Float2 position, float width);
public:
	QuadTree();
	QuadTree(const QuadTree &parent);
	~QuadTree();

	bool Initialize(std::vector<Mesh> *terrain, ID3D11Device *gDevice, ID3D11DeviceContext *gDeviceContext, RenderInstructions* worldBuffer);

	void Release();
	void GetQuadTreeRenderInfo(RenderInstructions * toRender);
	int  GetDrawCount();
};

