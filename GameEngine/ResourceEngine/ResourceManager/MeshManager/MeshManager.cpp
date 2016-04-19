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
}

void MeshManager::Release()
{
	for (size_t i = 0; i < gameMeshes->size(); i++)
	{
		gameMeshes->at(i).Release();
	}
	placeHolder.Release();

}

void MeshManager::GetMeshRenderInfo(Meshes * meshEnum, RenderInstructions * toRender)
{
}



#pragma region This function creates a cube that we use for early testing
void MeshManager::CreatePlaceHolder()
{

	Vertex cubeVerts[8];

	cubeVerts[0].position = Float3(-0.5,	  0.5,		  0.5);		//0
	cubeVerts[1].position = Float3(-0.5,	 -0.5,		  0.5);		//1
	cubeVerts[2].position = Float3(0.5,		 -0.5,		  0.5);		//2
	cubeVerts[3].position = Float3(0.5,		  0.5,		  0.5);		//3
	cubeVerts[4].position = Float3(0.5 ,	 -0.5  ,	 -0.5);		//4
	cubeVerts[5].position = Float3(0.5 ,	  0.5 ,		 -0.5);		//5
	cubeVerts[6].position = Float3(-0.5 ,	 -0.5 ,		 -0.5);		//6
	cubeVerts[7].position = Float3(-0.5 ,	  0.5 ,		 -0.5);		//7





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


void MeshManager::GetPlaceHolderMeshInfo(RenderInstructions * toRender)
{
	placeHolder.GetMeshRenderInfo(toRender);

}
#pragma endregion
