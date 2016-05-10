#include "Mesh.h"
#include "../QuadTree/QuadTree.h"



Mesh::Mesh(bool hasSkeleton, unsigned int skeletonID, unsigned int materialID)
{
	this->hasSkeleton = hasSkeleton;
	this->skeletonID = skeletonID;
	this->materialID = materialID;
}

Mesh::Mesh()
{
	
}


Mesh::~Mesh()
{
	if (vertices != nullptr)
		delete vertices;

	if (animVertices != nullptr)
		delete animVertices;


}

void Mesh::Initialize(ID3D11Device *gDevice, ID3D11DeviceContext* gDeviceContext)
{
	//ObjectNode::Initialize(gDevice, gDeviceContext);
	this->gDevice = gDevice;
	this->gDeviceContext = gDeviceContext;
}

void Mesh::Release()
{
	SAFE_RELEASE(vertexBuffer);
	SAFE_RELEASE(indexBuffer);
}

void Mesh::GetMeshRenderInfo(RenderInstructions * toRender)
{
	toRender->isAnimated	=	&this->hasSkeleton;

	toRender->indexBuffer	=	 this->indexBuffer;
	toRender->indexCount	=	&this->indexCount;

	toRender->vertexBuffer  =	 this->vertexBuffer;
	toRender->vertexCount	=	&this->vertCount;

	toRender->materialID	=	 this->materialID;
}

void Mesh::CreateVertexBuffer(Vertex * vertices, unsigned int amount, bool isScene)
{

	if (isScene == true)
	{
		this->sceneVerts = vertices;
		this->vertCount = amount;
		this->isScene = isScene;
	}
	else
	{
		if (this->vertexBuffer != nullptr)
			SAFE_RELEASE(vertexBuffer);
	
	

		D3D11_BUFFER_DESC bufferDesc;
		memset(&bufferDesc, 0, sizeof(bufferDesc));
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.ByteWidth = sizeof(Vertex)* amount;



		D3D11_SUBRESOURCE_DATA data;
		//Send the array of vertices in to pSysMem
		data.pSysMem = vertices;
		HRESULT hr;
		hr = gDevice->CreateBuffer(&bufferDesc, &data, &vertexBuffer);

		if (FAILED(hr))
			MessageBox(NULL, L"Error creating vertexbuffer", L"Error in mesh class", MB_ICONERROR | MB_OK);
	
		this->vertCount = amount;
		this->isScene = isScene;
	}
	



}

void Mesh::CreateVertexBuffer(AnimVert * vertices, unsigned int amount)
{
	if (this->vertexBuffer != nullptr)
		SAFE_RELEASE(vertexBuffer);
		
	


	D3D11_BUFFER_DESC bufferDesc;
	memset(&bufferDesc, 0, sizeof(bufferDesc));
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(AnimVert)* amount;


	D3D11_SUBRESOURCE_DATA data;
	//Send the array of vertices in to pSysMem
	data.pSysMem = vertices;
	HRESULT hr;
	hr = gDevice->CreateBuffer(&bufferDesc, &data, &vertexBuffer);

	if (FAILED(hr))
		MessageBox(NULL, L"Error creating vertexbuffer", L"Error in mesh class", MB_ICONERROR | MB_OK);

	this->vertCount = amount;
	this->isScene = isScene;
}

void Mesh::setSceneVertexBuffer(unsigned int amount, ID3D11Buffer * vertexBuffer)
{
	this->vertexBuffer = vertexBuffer;
	this->vertCount = amount;
	if (this->isScene != true)
	{
		this->isScene = true;
	}
}

void Mesh::setSceneIndexBuffer(UINT amount, ID3D11Buffer * indexBuffer)
{
	this->indexBuffer = indexBuffer;
	this->vertCount = amount;
	if (this->isScene != true)
	{
		this->isScene = true;
	}
}

void Mesh::CreateIndexBuffer(UINT * indices, unsigned int amount, bool isScene)
{

	if (isScene == true)
	{
		this->sceneIndex = indices;
		this->indexCount = (UINT)amount;
		this->isScene = isScene;
	}
	else
	{
		if (this->indexBuffer != nullptr)
			SAFE_RELEASE(indexBuffer);
		
	

		D3D11_BUFFER_DESC ibd;

		ibd.Usage = D3D11_USAGE_IMMUTABLE;
		ibd.ByteWidth = sizeof(UINT) * amount;
		ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibd.CPUAccessFlags = 0;
		ibd.MiscFlags = 0;
		ibd.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA ibdData;
		ibdData.pSysMem = indices;

		HRESULT hr;
		hr = gDevice->CreateBuffer(&ibd, &ibdData, &indexBuffer);

		if(FAILED(hr))
			MessageBox(NULL, L"Error creating indexbuffer", L"Error in mesh class", MB_ICONERROR | MB_OK);

		this->indexCount = (UINT)amount;
		this->isScene = isScene;

	}

}
