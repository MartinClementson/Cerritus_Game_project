#include "QuadTree.h"
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

	/*
	This function does all the drawing for the visible nodes in the quad tree. It takes as input the frustum to check if the camera can see each quad
	It is recursive and calls itself for all the child nodes it can see
	*/

	/*
	IMPORTANT!
	The terrain shader has to be set as the active shader in engine before this is called
	*/

	//reset the number of triangles drawn for this frame
	//sendToConstantBuffer();

	//Render each node that is visible, starting at the parent node and moving down the tree
	RenderNode(m_parentNode, gDeviceContext, frustum, worldBuffer);


	bool result;
	int count, i;
	unsigned int stride, offset;

	//Do a frustum check on the cube

	//Check if the node can be viewed,
	//result = true;
	result = frustum->CheckCube(node->position.x, 0.0f, node->position.y, (node->width / 2.0f));

	//if it can't be seen then none of it's children can either so don't continue
	if (!result)
		return;

	//If this node can be seen, recursively call this function for each child node

	count = 0;
	for (i = 0; i < 4; i++)
	{
		if (node->nodes[i] != 0)
		{
			count++;
			RenderNode(node->nodes[i], gDeviceContext, frustum, worldBuffer);
		}

	}

	//If there were any children nodes then there is no need to continue, Parents have nothing to render
	if (count != 0)
		return;

	//Render the buffers in this node as normal if they can be seen

	stride = sizeof(Vertex);
	offset = 0;


	//DirectX::XMMATRIX world = DirectX::XMMatrixIdentity();
	//DirectX::XMFLOAT4X4 worldFloat;

	//DirectX::XMStoreFloat4x4(&worldFloat, world);
	//D3D11_MAPPED_SUBRESOURCE mappedResourceWorld;
	//ZeroMemory(&mappedResourceWorld, sizeof(mappedResourceWorld));

	////mapping to the matrixbuffer
	//gDeviceContext->Map(worldBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResourceWorld);

	//worldConstantBuffer* temporaryWorld = (worldConstantBuffer*)mappedResourceWorld.pData;

	//temporaryWorld->world = worldFloat;

	//gDeviceContext->Unmap(worldBuffer, 0);

	gDeviceContext->IASetVertexBuffers(0, 1, &node->vertexBuffer, &stride, &offset);

	gDeviceContext->IASetIndexBuffer(node->indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	gDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	gDeviceContext->DrawIndexed(node->triangleCount * 3, 0, 0);

	//increase the count of the numder of polygons that have been rendered during this frame
	m_drawCount += node->triangleCount;

	return;

}

void QuadTree::CalculateMeshDimensions(int count, Float2 & position, float & meshWidth)
{
	float maxWidth, maxDepth, minWidth, minDepth, width, depth, maxX, maxZ;

	//Center position of the mesh, Start at zero
	position.x = 0.0f;
	position.y = 0.0f;

	//Sum all the vertices in the mesh
	for (int i = 0; i < count; i++)
	{
		position.x += this->combinedvertices[this->combinedindices[i]].position.x;
		position.y += this->combinedvertices[this->combinedindices[i]].position.y;
	}
	//Divide the sum with the number of vertices to find the mid point in the mesh
	position.x = position.x / (float)count;
	position.y = position.y / (float)count;

	//Init the max and min size of the mesh
	maxWidth = 0.0f;
	maxDepth = 0.0f;

	//fabsf Return the absolute value of the argument as FLOAT
	minWidth = fabsf(this->combinedvertices[this->combinedindices[0]].position.x - position.x);
	minDepth = fabsf(this->combinedvertices[this->combinedindices[0]].position.y - position.y);

	//Loop through all the vertices and find the max/min width and depth
	for (int i = 0; i < count; i++)
	{

		width = fabsf(this->combinedvertices[this->combinedindices[i]].position.x - position.x);
		depth = fabsf(this->combinedvertices[this->combinedindices[i]].position.y - position.y);

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

void QuadTree::CreateTreeNode(NodeType * parent, Float2 position, float width, ID3D11Device * gDevice, std::vector<Mesh>* terrain)
{
	/* This function Builds the quad tree. It is recursive and therefore it will call itself numerous times
	It starts with the parent, Then goes down.
	When it reaches a leaf node, it loads the vertex data into that node
	*/

	int numTriangles, count, vertexCount, index, vertexIndex;
	unsigned int i;
	float offsetX, offsetZ;

	Vertex* vertices = nullptr;
	UINT* indices = nullptr;

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
	parent->isAnimated = false;
	parent->materialID = 3;

	//Count the number of triangles that are inside this node
	numTriangles = CountTriangles(position, width);
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
			Float2 posWithOffset;
			posWithOffset.x = (position.x + offsetX);
			posWithOffset.y = (position.y + offsetZ);
			count = CountTriangles(posWithOffset, (width / 2.0f));

			if (count > 0)
			{
				//If there are triangles inside where this new node would be, then we create the child node
				parent->nodes[i] = new NodeType;

				//Extend the tree starting from this new child node
				CreateTreeNode(parent->nodes[i], posWithOffset, (width / 2), gDevice, terrain);
			}

		}
		return;
	}

	//Case 3: If there are the right number of triangles, then create and load the vertex and index buffer
	//from the terrain list into this node.. (We have determined that this is a leaf node)

	parent->triangleCount = numTriangles;

	//Calculate the number of vertices
	vertexCount = numTriangles * 3;
	parent->VertexCount = vertexCount;
	parent->IndexCount = indexCount;
	//Create vertex array
	vertices = new Vertex[vertexCount];
	std::vector<Vertex> newVert;
	newVert.resize(vertexCount);
	std::vector<UINT> newInd;
	newInd.resize(this->indexCount);
	//Create the index array
	indices = new UINT[this->indexCount];
	//std::vector<UINT> indices2;

	//Initialize the index
	index = 0;
	UINT indexCount = 0;
	bool alreadyExist = false;
	//Loop through all the triangles in the vertex list

	for (i = 0; i < m_triangleCount; i++)
	{
		//If the triangle is inside this node then add it to the vertex array
		result = IsTriangleContained(i, position, width);

		if (result == true)
		{
			//Calculate the index into the terrain vertex list
			vertexIndex = i * 3;

			//Get the three vertices of this triangle from the vertex list.
			newVert[index] = this->combinedvertices[this->combinedindices[vertexIndex]];
			newInd[index] = index;
			index++;
			indexCount++;
			vertexIndex++;


			newVert[index] = this->combinedvertices[this->combinedindices[vertexIndex]];
			newInd[index] = index;
			index++;
			indexCount++;
			vertexIndex++;


			newVert[index] = this->combinedvertices[this->combinedindices[vertexIndex]];
			newInd[index] = index;
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
	vertexData.pSysMem = newVert.data();
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;
	HRESULT hr;
	//Create the vertex buffer
	hr = gDevice->CreateBuffer(&vertexBufferDesc, &vertexData, &parent->vertexBuffer);

	//Set up the description of the index buffer

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(UINT) * indexCount;
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
	this->nodeCount += 1;
	return;



}

int QuadTree::CountTriangles(Float2 position, float width)
{
	int count;
	unsigned int i;
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
	x1 = this->combinedvertices[this->combinedindices[vertexIndex]].position.x;
	z1 = this->combinedvertices[this->combinedindices[vertexIndex]].position.z;
	vertexIndex++;

	x2 = this->combinedvertices[this->combinedindices[vertexIndex]].position.x;
	z2 = this->combinedvertices[this->combinedindices[vertexIndex]].position.z;
	vertexIndex++;

	x3 = this->combinedvertices[this->combinedindices[vertexIndex]].position.x;
	z3 = this->combinedvertices[this->combinedindices[vertexIndex]].position.z;

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
	m_indexList = nullptr;
	m_parentNode = nullptr;
}

QuadTree::QuadTree(const QuadTree & parent)
{

}

QuadTree::~QuadTree()
{
	//delete[] m_vertexList;
	//delete[] m_indexList;
}

//FINHJISH ME!
bool QuadTree::Initialize(std::vector<Mesh> * terrain, ID3D11Device * gDevice, ID3D11DeviceContext * gDeviceContext)
{
	this->m_vertexList = new std::vector<Vertex*>;
	this->m_indexList = new std::vector<UINT*>;
	this->vertextest = new std::vector<Vertex>;
	this->indextest = new std::vector<UINT>;

	this->gDevice = gDevice;
	this->gDeviceContext = gDeviceContext;
	//this->worldMatrix = worldBuffer->worldBuffer.worldMatrix;

	this->vertexCount = 0;
	this->indexCount = 0;
	float width;
	Float2 position;
	for (size_t i = 0; i < m_parentNode->size(); i++)
	{

	}


	//Get the number of vertices in the terrain
	for (unsigned int i = 0; i < 4; i++)
	{
		this->vertexCount += terrain->at(i).GetVertexCount();
		 this->indexCount += terrain->at(i).GetIndexCount();
	}

	//Store the total triangle countW
	m_triangleCount = vertexCount / 3;


	for (unsigned int i = 0; i < 4; i++)
	{
		this->m_vertexList->push_back(terrain->at(i).GetVertices());
		 this->m_indexList->push_back(terrain->at(i).GetIndices());

	}
	//VARJE VECTORPLATS
	for (unsigned int arrayIndex = 0; arrayIndex < m_vertexList->size(); arrayIndex++)
	{
		//VARJE VERTEXARRAY I VECTORN
		for (unsigned int vertexAmountPerArray = 0; vertexAmountPerArray < terrain->at(arrayIndex).GetVertexCount(); vertexAmountPerArray++)
		{
			//VARJE VERTIS I VERTEXARRAY
			this->vertextest->push_back(m_vertexList->at(arrayIndex)[vertexAmountPerArray]);
		}
	}
	this->combinedvertices = vertextest->data();
	//VARJE VECTORPLATS
	for (unsigned int arrayIndex = 0; arrayIndex < m_indexList->size(); arrayIndex++)
	{
		//VARJE INDEXARRAY I VECTORN
		for (UINT IndexAmountPerArray = 0; IndexAmountPerArray < terrain->at(arrayIndex).GetIndexCount(); IndexAmountPerArray++)
		{
			//VARJE VERTIS I INDEXARRAY
			this->indextest->push_back(m_indexList->at(arrayIndex)[IndexAmountPerArray]);
		}
	}
	this->combinedindices = indextest->data();
												 //Calculate the parent node. It's the upper most quad, covering the whole terrain
												 //Calculates center x,z and width
	CalculateMeshDimensions(vertexCount, position, width);

	//Create the parent node of the mesh
	m_parentNode = new NodeType;
	if (!m_parentNode)
		return false;

	//Recursively build the quad tree, based on the vertex list and mesh dimensions
	CreateTreeNode(m_parentNode, position, width, gDevice, terrain);

	//Now the vertex list is no longer needed
	if (m_vertexList)
	{	
		for (size_t i = 0; i < m_vertexList->size(); i++)
		{
			delete m_vertexList->at(i);
		}
		delete m_vertexList;
	}

	if (m_indexList)
	{
		for (size_t i = 0; i < m_indexList->size(); i++)
		{
			delete m_indexList->at(i);
		}
		delete m_indexList;
	}

	if (vertextest)
	{
		delete vertextest;
	}

	if (indextest)
	{
		delete indextest;
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

void QuadTree::GetQuadTreeRenderInfo(std::vector<RenderInstructions>* toRender, Frustum* frustum)
{
	GetNodeRenderInfo(m_parentNode, toRender, frustum);
}

void QuadTree::GetNodeRenderInfo(NodeType * node, std::vector<RenderInstructions>* toRender, Frustum* frustum)
{
	RenderInstructions tempInstruction;// = new RenderInstructions();
	int i, count;

	bool result;
	result = frustum->CheckCube(node->position.x, 0.0f, node->position.y, (node->width / 2.0f));

	//if it can't be seen then none of it's children can either so don't continue
	if (!result)
		return;

	count = 0;
	for (i = 0; i < 4; i++)
	{
		if (node->nodes[i] != 0)
		{
			count++;
			GetNodeRenderInfo(node->nodes[i], toRender, frustum);
		}

	}

	if (count != 0)
		return;
	//normal procedures
	/*tempInstruction->vertexBuffer	 = node->vertexBuffer;
	tempInstruction->indexBuffer	 = node->indexBuffer;
	tempInstruction->materialID		 = node->materialID;

	tempInstruction->vertexCount	 = &node->VertexCount;
	tempInstruction->isAnimated		 = &node->isAnimated;*/
	//tempInstruction.worldBuffer

	tempInstruction.vertexBuffer	 = node->vertexBuffer;
	tempInstruction.indexBuffer		 = node->indexBuffer;
	tempInstruction.materialID		 = node->materialID;
				   
	tempInstruction.indexCount		 = &node->IndexCount;
	tempInstruction.vertexCount		 = &node->VertexCount;
	tempInstruction.isAnimated		 = &node->isAnimated;


	toRender->push_back(tempInstruction);

	//delete tempInstruction;
}

int QuadTree::GetDrawCount()
{
	return m_drawCount;
}
