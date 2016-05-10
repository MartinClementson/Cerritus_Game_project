#include "MeshManager.h"




MeshManager::MeshManager()
{
	this->gameMeshes = new std::vector<Mesh>;
	this->sceneMeshes = new std::vector<Mesh>;
	this->quadTree = new QuadTree;
}
MeshManager::~MeshManager()
{
	delete gameMeshes;
	delete sceneMeshes;
	delete quadTree;
}

void MeshManager::Initialize(ID3D11Device *gDevice, ID3D11DeviceContext* gDeviceContext)
{
	this->gDevice = gDevice;
	this->gDeviceContext = gDeviceContext;
	
	placeHolder.Initialize(gDevice,gDeviceContext);
	CreatePlaceHolder();

	placeHolderPlane.Initialize(gDevice, gDeviceContext);
	CreatePlaceHolderPlane();

	fullScreenQuad.Initialize(gDevice, gDeviceContext);
	CreateFullScreenQuad();
}

void MeshManager::Release()
{
	for (size_t i = 0; i < gameMeshes->size(); i++)
	{
		gameMeshes->at(i).Release();
	}
	placeHolder.Release();
	placeHolderPlane.Release();
	fullScreenQuad.Release();
	quadTree->Release();
}

void MeshManager::AddMesh(bool hasSkeleton, unsigned int skeletonID, int materialID, unsigned int vertexCount, UINT indexCount, std::vector<Vertex> vertices, std::vector<AnimVert> aniVertices, std::vector<UINT> indices, bool isScene)
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
		newMesh.CreateVertexBuffer(newVertices, vertexCount, isScene);
		newMesh.CreateIndexBuffer(newIndices, indexCount, isScene);
		if (isScene == true)
			this->sceneMeshes->push_back(newMesh);
		else
		{
			this->gameMeshes->push_back(newMesh);
			delete[] newVertices;
			delete[] newIndices;
		}
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
		newMesh.CreateIndexBuffer(newIndices, indexCount, isScene);
		this->gameMeshes->push_back(newMesh);
		delete[] newVertices;
		delete[] newIndices;
	}
}


//int MeshManager::GetMaterialID(unsigned int index)
//{
//	return gameMeshes->at(index);
//}



void MeshManager::CreateQuadTree(RenderInstructions* currentMesh)
{
	this->quadTree->Initialize(this->sceneMeshes, this->gDevice, this->gDeviceContext, currentMesh);
}

void MeshManager::GetMeshRenderInfo(MeshEnum * meshEnum, RenderInstructions * toRender)
{
	if(*meshEnum == MeshEnum::MAIN_CHARACTER)
		this->gameMeshes->at(0).GetMeshRenderInfo(toRender);

	else if (*meshEnum == MeshEnum::ENEMY_1)
		this->gameMeshes->at(1).GetMeshRenderInfo(toRender);
	else if (*meshEnum == MeshEnum::TRAP_BEAR)
	{
		this->gameMeshes->at(2).GetMeshRenderInfo(toRender);
	}
	else if (*meshEnum == MeshEnum::TRAP_FIRE)
		this->gameMeshes->at(3).GetMeshRenderInfo(toRender);
	else if (*meshEnum == MeshEnum::SCENE)
	{
		//this->gameMeshes->at(4).SetMaterialID(3); //FULLÖSNING
		//this->gameMeshes->at(4).GetMeshRenderInfo(toRender);
		//this->gameMeshes->at(5).GetMeshRenderInfo(toRender);
		//this->gameMeshes->at(6).GetMeshRenderInfo(toRender);
		//this->gameMeshes->at(7).GetMeshRenderInfo(toRender);
		this->quadTree->GetQuadTreeRenderInfo(toRender);
	}
	else if (*meshEnum == MeshEnum::PROJECTILE_1)
		this->gameMeshes->at(8).GetMeshRenderInfo(toRender);
	else
		this->placeHolder.GetMeshRenderInfo(toRender);


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
	
	this->placeHolder.CreateVertexBuffer(cubeVerts, 8, false);
	this->placeHolder.CreateIndexBuffer(indices, 36, false);


}

void MeshManager::CreatePlaceHolderPlane()
{

	Vertex planeVerts[4];

	planeVerts[0].position = Float3(-200.0f, -0.1f, 200.0f);		//0
	planeVerts[0].uv.x = 0.0f;
	planeVerts[0].uv.y = 0.0f;
	planeVerts[0].normal = Float3(0.0f, 1.0f, 0.0f);
	

	planeVerts[1].position = Float3(200.0f, -0.1f, 200.0f);		//3
	planeVerts[1].uv.x = 1.0;
	planeVerts[1].uv.y = 0.0f;
	planeVerts[1].normal = Float3(0.0f, 1.0f, 0.0f);

	planeVerts[2].position = Float3(200.0f, -0.1f, -200.0f);		//5
	planeVerts[2].uv.x = 1.0f;
	planeVerts[2].uv.y = 1.0f;
	planeVerts[2].normal = Float3(0.0f, 1.0f, 0.0f);

	planeVerts[3].position = Float3(-200.0f, -0.1f, -200.0f);		//7
	planeVerts[3].uv.x = 0.0f;
	planeVerts[3].uv.y = 1.0f;
	planeVerts[3].normal = Float3(0.0f, 1.0f, 0.0f);

	UINT indices[6] =
	{
		0, 1, 2,
		0, 2, 3
	};


	

	this->placeHolderPlane.CreateVertexBuffer(planeVerts, 4, false);
	this->placeHolderPlane.CreateIndexBuffer(indices, 6, false);
	
}

void MeshManager::CreateFullScreenQuad()
{

	Vertex planeVerts[4];

	planeVerts[0].position = Float3(-1.0f,	1.0f,  0.0f);		//0
	planeVerts[0].uv.x = 0.0f;
	planeVerts[0].uv.y = 0.0f;

	planeVerts[1].position = Float3(1.0f,	1.0f,  0.0f);		//1
	planeVerts[1].uv.x = 1.0f;
	planeVerts[1].uv.y = 0.0f;

	planeVerts[2].position = Float3(1.0f,	-1.0f, 0.0f);		//2
	planeVerts[2].uv.x = 1.0f;
	planeVerts[2].uv.y = 1.0f;

	planeVerts[3].position = Float3(-1.0f, -1.0f, 0.0f);		//3
	planeVerts[3].uv.x = 0.0f;
	planeVerts[3].uv.y = 1.0f;


	UINT indices[6] =
	{
		0, 1, 2,
		0, 2, 3
	};




	this->fullScreenQuad.CreateVertexBuffer(planeVerts, 4, false);
	this->fullScreenQuad.CreateIndexBuffer(indices, 6, false);


}


void MeshManager::GetPlaceHolderMeshInfo(RenderInstructions * toRender)
{
	//this->gameMeshes->at(1).GetMeshRenderInfo(toRender);
	placeHolder.GetMeshRenderInfo(toRender);

}
void MeshManager::GetPlaceHolderPlaneInfo(RenderInstructions * toRender)
{
	placeHolderPlane.GetMeshRenderInfo(toRender);
}
void MeshManager::GetFullScreenQuadInfo(RenderInstructions * toRender)
{
	fullScreenQuad.GetMeshRenderInfo(toRender);
}
#pragma endregion
