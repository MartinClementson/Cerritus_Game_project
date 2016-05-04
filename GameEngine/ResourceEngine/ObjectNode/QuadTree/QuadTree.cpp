#include "QuadTree.h"
//FINISH ME might be depricated
void QuadTree::UpdateWorldMatrix()
{
}
//FINISH ME might be depricated
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
	/* This function Builds the quad tree. It is recursive and therefore it will call itself numerous times
	It starts with the parent, Then goes down.
	When it reaches a leaf node, it loads the vertex data into that node
	*/

	int numTriangles, i, count, vertexCount, index, vertexIndex;

	float offsetX, offsetZ;

	Vertex* vertices;

	unsigned long* indices;

	bool result;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;

	//Initialize the node and set it's position in the world

	//Store the node position and size
	parent->position.x = position.x;
	parent->position.y = position.y;
	parent->width = width;

	//Set triangle count to Zero

	parent->triangleCount = 0;

	//Set index and vertex buffers to null;
	parent->indexBuffer = 0;
	parent->vertexBuffer = 0;

	//Set the children nodes of this node to null
	parent->nodes[0] = 0;
	parent->nodes[1] = 0;
	parent->nodes[2] = 0;
	parent->nodes[3] = 0;

	//Count the number of triangles that are inside this node
	numTriangles = countTriangles(x, z, width);
	/*
	PROBLEM!

	numTriangles always get's the same amount!!

	Update: 29/2.
	Now it seems like it splits the vertices up like it should, and stops when it goes below 10k.
	However it is hard to see what nodes are being processed. But this does not seem to be the problem no more. Might still be something fishy though.
	*/


	//Case 1: If there are no triangles in this node, return it as empty
	if (numTriangles == 0)
		return;

	//Case 2: IF there are too many triangles in this node, then split it into four smaller nodes
	if (numTriangles > maxTriangles)
	{
		for (i = 0; i < 4; i++)
		{
			//Calculate position offset for the new child node
			if (float(i % 2) < 1)							//
				offsetX = -1.0f * (width / 4.0f);		// c-style representation would be
			else                                        // offsetX = (((i % 2) < 1) ? -1.0f : 1.0f) * (width / 4.0f);
				offsetX = 1.0f * (width / 4.0f);        // condition ? valueIfTrue : valueIfFalse
														// Changed to c++ if statement for easier understanding

			if (float(i % 4) < 2)
				offsetZ = -1.0f * (width / 4.0f);
			else
				offsetZ = 1.0f * (width / 4.0f);
			//offsetX = (((i % 2) < 1) ? -1.0f : 1.0f) * (width / 4.0f);
			//offsetZ = (((i % 4) < 2) ? -1.0f : 1.0f) * (width / 4.0f);


			//See if there are any triangles in the new node
			count = countTriangles((x + offsetX), (z + offsetZ), (width / 2.0f));

			if (count > 0)
			{
				//If there are triangles inside where this new node would be, then we create the child node
				parent->nodes[i] = new NodeType;

				//Extend the tree starting from this new child node
				createTreeNode(parent->nodes[i], (x + offsetX), (z + offsetZ), (width / 2), gDevice);
			}

		}
		return;
	}

	//Case 3: If there are the right number of triangles, then create and load the vertex and index buffer
	//from the terrain list into this node.. (We have determined that this is a leaf node)

	parent->triangleCount = numTriangles;

	//Calculate the number of vertices
	vertexCount = numTriangles * 3;

	//Create vertex array
	vertices = new Vertex[vertexCount];

	//Create the index array
	indices = new unsigned long[vertexCount];
	//std::vector<UINT> indices2;

	//Initialize the index
	index = 0;
	UINT indexCount = 0;
	bool alreadyExist = false;
	//Loop through all the triangles in the vertex list

	for (i = 0; i < m_triangleCount; i++)
	{
		//If the triangle is inside this node then add it to the vertex array
		result = isTriangleContained(i, x, z, width);

		if (result == true)
		{
			//Calculate the index into the terrain vertex list
			vertexIndex = i * 3;

			//Get the three vertices of this triangle from the vertex list.
			vertices[index] = m_vertexList[m_indexList[vertexIndex]];
			indices[index] = index;
			index++;
			indexCount++;
			vertexIndex++;


			vertices[index] = m_vertexList[m_indexList[vertexIndex]];
			indices[index] = index;
			index++;
			indexCount++;
			vertexIndex++;


			vertices[index] = m_vertexList[m_indexList[vertexIndex]];
			indices[index] = index;
			index++;
			indexCount++;


		}


	}

	//Set up the description for the vertex buffer
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(Vertex)* vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	//Give the subresource structure a pointer to the vertex data
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;
	HRESULT hr;
	//Create the vertex buffer
	hr = gDevice->CreateBuffer(&vertexBufferDesc, &vertexData, &parent->vertexBuffer);

	//Set up the description of the index buffer

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * vertexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	//Give the subresource structure a pointer to the index data
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	//Create index buffer
	hr = gDevice->CreateBuffer(&indexBufferDesc, &indexData, &parent->indexBuffer);

	//Delete the vertices and indices arrays, as they are now stored in the buffers

	delete[] vertices;
	vertices = 0;
	delete[] indices;
	indices = 0;

	return;



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
bool QuadTree::Initialize(Mesh * scene, ID3D11Device * gDevice, ID3D11DeviceContext * gDeviceContext, ID3D11Buffer * worldBuffer)
{

	this->worldBuffer = worldBuffer;		//blir nog en helt ny ist
	this->gDeviceContext = gDeviceContext;
	this->gDevice = gDevice;
	this->worldStruct = new worldConstantBuffer;
	this->updateWorldMatrix();

	int vertexCount, indexCount;
	float width;
	Float2 centerPos;

	//Get the number of vertices in the terrain
	vertexCount = scene->GetVertexCount();
	this->indexCount = scene->GetIndexCount();

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
	scene->copyVertexArray((void*)m_vertexList);
	scene->copyIndexArray((void*)m_indexList); //<-- this could be wrong
												 //Calculate the parent node. It's the upper most quad, covering the whole terrain
												 //Calculates center x,z and width
	CalculateMeshDimensions(vertexCount, centerPos.x, centerPos.y, width);

	//Create the parent node of the mesh
	m_parentNode = new NodeType;
	if (!m_parentNode)
		return false;

	//Recursively build the quad tree, based on the vertex list and mesh dimensions
	CreateTreeNode(m_parentNode, centerPos, width, gDevice);

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
