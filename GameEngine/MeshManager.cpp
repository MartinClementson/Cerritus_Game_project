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
	for (int i = 0; i < gameMeshes->size(); i++)
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
	//Vertex cubeVerts[36];

	//cubeVerts[0].Position = Double3(-0.5, 0.5, 0.5);	//1

	//cubeVerts[1].Position = Double3(-0.5, -0.5, 0.5);	//2

	//cubeVerts[2].Position = Double3(0.5, -0.5, 0.5);	//3


	//cubeVerts[3].Position = Double3(-0.5, 0.5, 0.5);	//1

	//cubeVerts[4].Position = Double3(0.5, -0.5, 0.5);	//3

	//cubeVerts[5].Position = Double3(0.5, 0.5, 0.5);		//4



	//cubeVerts[6].Position = Double3(0.5 , 0.5 , 0.5);	//4

	//cubeVerts[7].Position = Double3(0.5 , -0.5 , 0.5);	//3

	//cubeVerts[8].Position = Double3(0.5 , -0.5  , -0.5); //5



	//cubeVerts[9].Position = Double3(0.5 , 0.5 , 0.5); //4

	//cubeVerts[10].Position = Double3(0.5 , -0.5 , -0.5); //5

	//cubeVerts[11].Position = Double3(0.5 , 0.5 , -0.5); //6



	//cubeVerts[12].Position = Double3(0.5 , 0.5 , -0.5); //6

	//cubeVerts[13].Position = Double3(0.5 , -0.5 , -0.5); //5

	//cubeVerts[14].Position = Double3(-0.5 , -0.5 , -0.5); //7




	//cubeVerts[15].Position = Double3(0.5 , 0.5 , -0.5); //6

	//cubeVerts[16].Position = Double3(-0.5 , -0.5 , -0.5); //7

	//cubeVerts[17].Position = Double3(-0.5 , 0.5 , -0.5); //8



	//cubeVerts[18].Position = Double3(-0.5 , 0.5 , -0.5);	//8

	//cubeVerts[19].Position = Double3(-0.5 , -0.5 , -0.5);	//7

	//cubeVerts[20].Position = Double3(-0.5 , -0.5 , 0.5);	//2

	//
	//cubeVerts[21].Position = Double3(-0.5 , 0.5 , -0.5); //8

	//cubeVerts[22].Position = Double3(-0.5 , -0.5 , 0.5); //2

	//cubeVerts[24].Position = Double3(-0.5 , 0.5 , 0.5); //1


	//cubeVerts[25].Position = Double3(-0.5 , 0.5 , 0.5); //1

	//cubeVerts[26].Position = Double3(0.5 , 0.5 , 0.5); //4

	//cubeVerts[27].Position = Double3(0.5 , 0.5 , -0.5); //6



	//cubeVerts[28].Position = Double3(-0.5 , 0.5 , 0.5); //1

	//cubeVerts[29].Position = Double3(0.5 , 0.5 , -0.5); //4

	//cubeVerts[30].Position = Double3(-0.5 , 0.5 , -0.5); //8



	//cubeVerts[31].Position = Double3(-0.5 , -0.5 , 0.5); //2

	//cubeVerts[32].Position = Double3(0.5 , -0.5 , -0.5); //5

	//cubeVerts[33].Position = Double3(0.5 , -0.5 , 0.5); //3




	//cubeVerts[34].Position = Double3(-0.5 , -0.5 , 0.5); //2

	//cubeVerts[35].Position = Double3(-0.5 , -0.5 , -0.5); //7

	//cubeVerts[36].Position = Double3(0.5 , -0.5 , -0.5);//5
	
	
	//Vertex cubeVerts[8];

	//cubeVerts[0].Position = Float3(-0.5, 0.5, 0.5);		 //0
	//cubeVerts[0].Position = Float3(-0.5, -0.5, 0.5);	 //1
	//cubeVerts[2].Position = Float3(0.5, -0.5, 0.5);		 //2
	//cubeVerts[3].Position = Float3(0.5, 0.5, 0.5);		 //3
	//cubeVerts[4].Position = Float3(0.5 , -0.5  , -0.5);  //4
	//cubeVerts[5].Position = Float3(0.5 , 0.5 , -0.5);	 //5
	//cubeVerts[6].Position = Float3(-0.5 , -0.5 , -0.5);  //6
	//cubeVerts[7].Position = Float3(-0.5 , 0.5 , -0.5);   //7





	//UINT indices[36] = { 0,1,2,   0,2,3,     3,2,4,     3,4,5,    5,4,6,       5,6,7,    7,6,1,     7,1,0,    0,3,5,    0,3,7,    1,4,2,     1,6,4 };
	//
	//this->placeHolder.CreateVertexBuffer(cubeVerts, 8);
	//this->placeHolder.CreateIndexBuffer(indices, 36);




	Vertex triangleVertices[3];

		triangleVertices[0] = Float3(0.0f, 0.5f, 0.0f);	//v0 pos
		

		triangleVertices[1] = Float3(0.5f, -0.5f, 0.0f); //v1
		

		triangleVertices[2] = Float3(-0.5f, -0.5f, 0.0f); //v2
		
		
		UINT indices[3] = { 0,1,2 };

		this->placeHolder.CreateVertexBuffer(triangleVertices, 3);
		this->placeHolder.CreateIndexBuffer(indices, 3);


}


void MeshManager::GetPlaceHolderMeshInfo(RenderInstructions * toRender)
{
	placeHolder.GetMeshRenderInfo(toRender);

}
#pragma endregion
