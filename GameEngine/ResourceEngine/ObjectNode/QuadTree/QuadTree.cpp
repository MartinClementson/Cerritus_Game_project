#include "QuadTree.h"
//FINISH ME
void QuadTree::UpdateWorldMatrix()
{
}
//FINISH ME
void QuadTree::SendToConstantBuffer()
{
}

void QuadTree::ReleaseNode(NodeType * node)
{
	int i;

	//Go down the tree and release the bottom nodes first

	for (i = 0; i < 4; i++)
	{
		if (node->nodes[i] != 0)
			ReleaseNode(node->nodes[i]);

	}

	//Release the vertex buffer for this node

	if (node->vertexBuffer)
	{
		node->vertexBuffer->Release();
		node->vertexBuffer = 0;
	}
	//Release index buffer fopr this node
	if (node->indexBuffer)
	{
		node->indexBuffer->Release();
		node->indexBuffer = 0;
	}

	//Release the four child nodes
	for (i = 0; i < 4; i++)
	{
		if (node->nodes[i])
		{
			delete node->nodes[i];
			node->nodes[i] = 0;
		}

	}
	return;
}

void QuadTree::RenderNode(NodeType * node, ID3D11DeviceContext * gDeviceContext, Frustum * frustum, ID3D11Buffer * worldBuffer)
{
}

void QuadTree::CalculateMeshDimensions(int count, float & x, float & z, float & meshWidth)
{
	float maxWidth, maxDepth, minWidth, minDepth, width, depth, maxX, maxZ;

	//Center position of the mesh, Start at zero
	x = 0.0f;
	z = 0.0f;

	//Sum all the vertices in the mesh
	for (int i = 0; i < count; i++)
	{
		x += m_vertexList[m_indexList[i]].position.x;
		z += m_vertexList[m_indexList[i]].position.z;
	}
	//Divide the sum with the number of vertices to find the mid point in the mesh
	x = x / (float)count;
	z = z / (float)count;

	//Init the max and min size of the mesh
	maxWidth = 0.0f;
	maxDepth = 0.0f;

	//fabsf Return the absolute value of the argument as FLOAT
	minWidth = fabsf(m_vertexList[m_indexList[0]].position.x - x);
	minDepth = fabsf(m_vertexList[m_indexList[0]].position.z - z);

	//Loop through all the vertices and find the max/min width and depth
	for (int i = 0; i < count; i++)
	{

		width = fabsf(m_vertexList[m_indexList[i]].position.x - x);
		depth = fabsf(m_vertexList[m_indexList[i]].position.z - z);

		if (width > maxWidth) { maxWidth = width; }
		if (depth > maxDepth) { maxDepth = depth; }
		if (width < minWidth) { minWidth = width; }
		if (depth < minDepth) { minDepth = depth; }
	}

	//Find the absolute max calue between the min and max depth and width
	maxX = (float)max(fabs(minWidth), fabs(maxWidth));
	maxZ = (float)max(fabs(minDepth), fabs(maxDepth));


	//Calculate the maximum diameter of the mesh
	meshWidth = max(maxX, maxZ) * 2.0f;

	return;
}

void QuadTree::CreateTreeNode(NodeType * parent, Float2 position, float width, ID3D11Device * gDevice)
{
}

int QuadTree::CountTriangles(Float2 position, float width)
{
	int count, i;
	bool result;

	count = 0;
	//Loop through all the triangles in the entire mesh and check wich ones should be inside this node

	for (i = 0; i < m_triangleCount; i++)
	{
		//if the triangle is inside the node then add one to count
		result = IsTriangleContained(i, position, width);
		if (result == true)
		{
			count++;
		}

	}


	return count;
}

bool QuadTree::IsTriangleContained(int index, Float2 position, float width)
{
	float radius;
	int vertexIndex;
	float x1, z1, x2, z2, x3, z3;
	float minX, maxX, minZ, maxZ;

	//Calculate radius of this node
	radius = width / 2.0f;

	//Get the index into the vertex list
	vertexIndex = index * 3;

	//Get the three vertices of this triangle from the vertex list
	x1 = m_vertexList[m_indexList[vertexIndex]].position.x;
	z1 = m_vertexList[m_indexList[vertexIndex]].position.z;
	vertexIndex++;

	x2 = m_vertexList[m_indexList[vertexIndex]].position.x;
	z2 = m_vertexList[m_indexList[vertexIndex]].position.z;
	vertexIndex++;

	x3 = m_vertexList[m_indexList[vertexIndex]].position.x;
	z3 = m_vertexList[m_indexList[vertexIndex]].position.z;

	//Check if the minimum of the x coords of the triangle is inside the node
	minX = min(x1, min(x2, x3));
	if (minX > (position.x + radius))
		return false;

	//Check if the maximum of the x coords is inside the node
	maxX = max(x1, max(x2, x3));
	if (maxX < (position.x - radius))
		return false;


	//check if the minimum of the z coords is inside the node
	minZ = min(z1, min(z2, z3));
	if (minZ >(position.y + radius))
		return false;

	//Check if the maximum z coord are inside the node
	maxZ = max(z1, max(z2, z3));
	if (maxZ < (position.y - radius))
		return false;


	return true;
}

QuadTree::QuadTree()
{
	m_vertexList = nullptr;
	m_parentNode = nullptr;
}

QuadTree::QuadTree(const QuadTree & parent)
{
}

QuadTree::~QuadTree()
{
	delete[] m_vertexList;
	delete[] m_indexList;
}

//FINHJISH ME!
bool QuadTree::Initialize(Mesh * terrain, ID3D11Device * gDevice, ID3D11DeviceContext * gDeviceContext, ID3D11Buffer * worldBuffer)
{

	this->worldBuffer = worldBuffer;
	this->gDeviceContext = gDeviceContext;
	this->worldStruct = new worldConstantBuffer;
	this->updateWorldMatrix();

	int vertexCount, indexCount;
	float centerX, centerZ, width;


	//Get the number of vertices in the terrain
	vertexCount = terrain->getVertexCount();
	this->indexCount = terrain->getIndexCount();

	//Store the total triangle countW
	m_triangleCount = this->indexCount / 3;

	m_indexList = new unsigned long[this->indexCount];
	if (!m_indexList)
		return false;
	//create a vertex array to hold all of the terrain vertices
	m_vertexList = new Vertex[vertexCount];
	if (!m_vertexList)
		return false;

	//Copy the vertices from the terrain into the vertex list
	terrain->copyVertexArray((void*)m_vertexList);
	terrain->copyIndexArray((void*)m_indexList); //<-- this could be wrong

												 //Calculate the parent node. It's the upper most quad, covering the whole terrain
												 //Calculates center x,z and width
	CalculateMeshDimensions(vertexCount, centerX, centerZ, width);

	//Create the parent node of the mesh
	m_parentNode = new NodeType;
	if (!m_parentNode)
		return false;

	//Recursively build the quad tree, based on the vertex list and mesh dimensions
	createTreeNode(m_parentNode, centerX, centerZ, width, gDevice);

	//Now the vertex list is no longer needed
	if (m_vertexList)
	{
		delete[]m_vertexList;
		m_vertexList = 0;
	}
	if (m_indexList)
	{
		delete[]m_indexList;
		m_indexList = 0;
	}

	return true;
}

void QuadTree::Release()
{
	//Recursively release the quad tree data
	if (m_parentNode)
	{
		ReleaseNode(m_parentNode);
		delete m_parentNode;
		m_parentNode = 0;
	}
	return;
}

void QuadTree::Render(ID3D11DeviceContext * gDeviceContext, Frustum * frustum, ID3D11Buffer * worldBuffer)
{
	/*
	IMPORTANT!
	The terrain shader has to be set as the active shader in engine before this is called
	*/

	//reset the number of triangles drawn for this frame
	m_drawCount = 0;
	//sendToConstantBuffer();

	//Render each node that is visible, starting at the parent node and moving down the tree
	RenderNode(m_parentNode, gDeviceContext, frustum, worldBuffer);
}

int QuadTree::GetDrawCount()
{
	return m_drawCount;
}
