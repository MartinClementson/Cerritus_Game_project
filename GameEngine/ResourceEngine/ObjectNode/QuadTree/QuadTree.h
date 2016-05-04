//#pragma once
//#include "../LibIncluder.h"
//#include "../Constants.h"
//#include "../../Structs/DataTypes.h"
//#include "../Camera/Frustum/Frustum.h"
//#include "../../ResourceManager/MeshManager/MeshManager.h"
//using namespace DirectX;
//class QuadTree
//{
//private:
//	struct NodeType
//	{
//		Float2 position;
//		float width;
//		unsigned int triangleCount;
//		ID3D11Buffer *vertexBuffer;
//		ID3D11Buffer *indexBuffer;
//		NodeType* nodes[4];
//	};
//
//	ID3D11DeviceContext* gDeviceContext	 = nullptr;		//Devices
//	ID3D11Device* gDevice				 = nullptr;		//Devices
//
//	ID3D11Buffer* worldBuffer			 = nullptr;		//ptr to engine world constantbuffer
//
//	XMFLOAT4X4 worldMatrix;
//	XMFLOAT4X4 normalWorld;								//might be depricated
//
//	void UpdateWorldMatrix();
//	void SendToConstantBuffer();
//
//
//	unsigned int	 m_triangleCount;
//	unsigned int	 m_drawCount;
//	Vertex*			 m_vertexList;
//	NodeType*		 m_parentNode;
//	unsigned long*	 m_indexList;
//
//	unsigned int indexCount;
//
//	void ReleaseNode(NodeType *node);
//	void RenderNode(NodeType *node, ID3D11DeviceContext *gDeviceContext, Frustum* frustum, ID3D11Buffer* worldBuffer);
//	void CalculateMeshDimensions(int count, float &x, float &z, float &meshWidth);
//	void CreateTreeNode(NodeType *parent, Float2 position, float width, ID3D11Device *gDevice);
//	int	 CountTriangles(Float2 position, float width);
//	bool IsTriangleContained(int index, Float2 position, float width);
//public:
//	QuadTree();
//	QuadTree(const QuadTree &parent);
//	~QuadTree();
//
//	bool Initialize(Mesh *terrain, ID3D11Device *gDevice, ID3D11DeviceContext *gDeviceContext, ID3D11Buffer* worldBuffer);
//	void Release();
//	void Render(ID3D11DeviceContext *gDeviceContext, Frustum * frustum, ID3D11Buffer* worldBuffer);
//	int  GetDrawCount();
//};