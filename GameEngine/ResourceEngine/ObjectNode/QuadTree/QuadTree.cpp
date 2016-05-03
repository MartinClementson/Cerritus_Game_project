#include "QuadTree.h"

void QuadTree::UpdateWorldMatrix()
{
}

void QuadTree::SendToConstantBuffer()
{
}

void QuadTree::ReleaseNode(NodeType * node)
{
}

void QuadTree::RenderNode(NodeType * node, ID3D11DeviceContext * gDeviceContext, Frustum * frustum, ID3D11Buffer * worldBuffer)
{
}

void QuadTree::CalculateMeshDimensions(int count, float & x, float & z, float & meshWidth)
{
}

void QuadTree::CreateTreeNode(NodeType * parent, Float2 position, float width, ID3D11Device * gDevice)
{
}

int QuadTree::CountTriangles(Float2 position, float width)
{
	return 0;
}

bool QuadTree::IsTriangleContained(int index, Float2 position, float width)
{
	return false;
}

QuadTree::QuadTree()
{
}

QuadTree::QuadTree(const QuadTree & parent)
{
}

QuadTree::~QuadTree()
{
}

bool QuadTree::Initialize(Mesh * terrain, ID3D11Device * gDevice, ID3D11DeviceContext * gDeviceContext, ID3D11Buffer * worldBuffer)
{
	return false;
}

void QuadTree::Release()
{
}

void QuadTree::Render(ID3D11DeviceContext * gDeviceContext, Frustum * frustum, ID3D11Buffer * worldBuffer)
{
}

int QuadTree::GetDrawCount()
{
	return 0;
}
