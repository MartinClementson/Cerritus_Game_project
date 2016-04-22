#include "MeshManager.h"




MeshManager::MeshManager()
{
	this->gameMeshes = new std::vector<Mesh>;

}
MeshManager::~MeshManager()
{
	delete gameMeshes;
}

void MeshManager::Initialize(ID3D11Device *gDevice, ID3D11DeviceContext* gDeviceContext)
{
	this->gDevice = gDevice;
	this->gDeviceContext = gDeviceContext;
	
	placeHolder.Initialize(gDevice,gDeviceContext);
	CreatePlaceHolder();

	placeHolderPlane.Initialize(gDevice, gDeviceContext);
	CreatePlaceHolderPlane();
}

void MeshManager::Release()
{
	for (size_t i = 0; i < gameMeshes->size(); i++)
	{
		gameMeshes->at(i).Release();
	}
	placeHolder.Release();
	placeHolderPlane.Release();

}

void MeshManager::AddMesh(bool hasSkeleton, unsigned int skeletonID, unsigned int materialID, unsigned int vertexCount, UINT indexCount, std::vector<Vertex> vertices, std::vector<AnimVert> aniVertices, std::vector<UINT> indices)
{
	if (aniVertices.size() <= 0)
	{
		Vertex* newVertices = new Vertex[vertexCount];
		for (unsigned int i = 0; i < vertexCount; i++)
		{
			newVertices[i] = vertices[i];
		}

		UINT* newIndices = new UINT[indexCount];
		for (unsigned int i = 0; i < indexCount; i++)
		{
			newIndices[i] = indices[i];
		}

		Mesh newMesh = Mesh(hasSkeleton, skeletonID, materialID);
		newMesh.Initialize(this->gDevice, this->gDeviceContext);
		newMesh.CreateVertexBuffer(newVertices, vertexCount);
		newMesh.CreateIndexBuffer(newIndices, indexCount);
		this->gameMeshes->push_back(newMesh);
		delete[] newVertices;
		delete[] newIndices;
	}
	else
	{
		AnimVert* newVertices = new AnimVert[vertexCount];
		for (unsigned int i = 0; i < vertexCount; i++)
		{
			newVertices[i] = aniVertices[i];
		}

		UINT* newIndices = new UINT[indexCount];
		for (unsigned int i = 0; i < indexCount; i++)
		{
			newIndices[i] = indices[i];
		}

		Mesh newMesh = Mesh(hasSkeleton, skeletonID, materialID);
		newMesh.Initialize(this->gDevice, this->gDeviceContext);
		newMesh.CreateVertexBuffer(newVertices, vertexCount);
		newMesh.CreateIndexBuffer(newIndices, indexCount);
		this->gameMeshes->push_back(newMesh);
		delete[] newVertices;
		delete[] newIndices;
	}
}


void MeshManager::GetMeshRenderInfo(MeshEnum * meshEnum, RenderInstructions * toRender)
{
}



#pragma region This function creates a cube that we use for early testing
void MeshManager::CreatePlaceHolder()
{

	Vertex cubeVerts[8];

	cubeVerts[0].position = Float3(-0.5,	  2.5,		  0.5);		//0
	cubeVerts[1].position = Float3(-0.5,	  0.0,		  0.5);		//1
	cubeVerts[2].position = Float3(0.5,		  0.0,		  0.5);		//2
	cubeVerts[3].position = Float3(0.5,		  2.5,		  0.5);		//3
	cubeVerts[4].position = Float3(0.5 ,	  0.0  ,	 -0.5);		//4
	cubeVerts[5].position = Float3(0.5 ,	  2.5 ,		 -0.5);		//5
	cubeVerts[6].position = Float3(-0.5 ,	  0.0 ,		 -0.5);		//6
	cubeVerts[7].position = Float3(-0.5 ,	  2.5 ,		 -0.5);		//7





	UINT indices[36] = 
	{ 
		0,1,2,  
		0,2,3,  
		3,2,4, 
		3,4,5,
		5,4,6,
		5,6,7,
		7,6,1,
		7,1,0,
		0,3,5, 
		0,5,7, 
		1,4,2, 
		1,6,4 };
	
	this->placeHolder.CreateVertexBuffer(cubeVerts, 8);
	this->placeHolder.CreateIndexBuffer(indices, 36);


}

void MeshManager::CreatePlaceHolderPlane()
{

	Vertex planeVerts[4];

	planeVerts[0].position = Float3(-200, -2.0, 200.0);		//0
	
	planeVerts[1].position = Float3(200.0, -2.0, 200.0);		//3
	
	planeVerts[2].position = Float3(200.0, -2.0, -200.0);		//5

	planeVerts[3].position = Float3(-200.0, -2.0, -200.0);		//7


	UINT indices[6] =
	{
		0, 1, 2,
		0, 2, 3
	};


	

	this->placeHolderPlane.CreateVertexBuffer(planeVerts, 4);
	this->placeHolderPlane.CreateIndexBuffer(indices, 6);

}


void MeshManager::GetPlaceHolderMeshInfo(RenderInstructions * toRender)
{
	//this->gameMeshes->at(0).GetMeshRenderInfo(toRender);
	placeHolder.GetMeshRenderInfo(toRender);

}
void MeshManager::GetPlaceHolderPlaneInfo(RenderInstructions * toRender)
{
	placeHolderPlane.GetMeshRenderInfo(toRender);
}
#pragma endregion
