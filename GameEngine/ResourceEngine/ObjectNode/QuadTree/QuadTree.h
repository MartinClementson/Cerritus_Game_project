#pragma once
#include "../LibIncluder.h"
#include "../Constants.h"
#include "../../Structs/DataTypes.h"
#include "../../Structs/RenderInfo.h"
#include "../Camera/Frustum/Frustum.h"
#include "../Mesh/Mesh.h"
using namespace DirectX;
//GLOBAL
const int maxTriangles = 20000;

class QuadTree
{
private:
	ID3D11DeviceContext* gDeviceContext			 = nullptr;		//Devices
	ID3D11Device* gDevice						 = nullptr;		//Devices

	ID3D11Buffer* worldBuffer					 = nullptr;		//ptr to engine world constantbuffer

	XMFLOAT4X4 worldMatrix;
	XMFLOAT4X4 normalWorld;										//might be depricated

	unsigned int			m_triangleCount;
	unsigned int			m_drawCount;
	std::vector<Vertex*>*	m_vertexList;
	std::vector<UINT*>*		m_indexList;
	std::vector<Vertex>*	vertextest;
	std::vector<UINT>*		indextest;
	std::vector<NodeType*>*	m_parentNode;

	Vertex* combinedvertices					 = nullptr;
	UINT* combinedindices						 = nullptr;

	unsigned int nodeCount;
	unsigned int vertexCount;
	UINT indexCount;

	void ReleaseNode(NodeType *node);
	void CalculateMeshDimensions(int count, Float2 & position, float &meshWidth);
	void CreateTreeNode(NodeType *parent, Float2 position, float width, ID3D11Device *gDevice, std::vector<Mesh>* terrain);
	int	 CountTriangles(Float2 position, float width);
	bool IsTriangleContained(int index, Float2 position, float width);
public:
	QuadTree();
	QuadTree(const QuadTree &parent);
	~QuadTree();

	bool Initialize(std::vector<Mesh> *terrain, ID3D11Device *gDevice, ID3D11DeviceContext *gDeviceContext);

	void Release();
	void GetQuadTreeRenderInfo(std::vector<RenderInstructions>* toRender, Frustum* frustum);
	void GetNodeRenderInfo(NodeType* node, std::vector<RenderInstructions>* toRender, Frustum* frustum);
	NodeType* GetParentNode(int index) { return this->m_parentNode->at(index); };
	unsigned int GetNodeCount() { return this->nodeCount; };
	int  GetDrawCount();
};

