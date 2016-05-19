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
	float x = 0;
	this->gDevice = gDevice;
	this->gDeviceContext = gDeviceContext;
	
	placeHolder.Initialize(gDevice,gDeviceContext);
	CreatePlaceHolder();

	placeHolderPlane.Initialize(gDevice, gDeviceContext);
	CreatePlaceHolderPlane();

	fullScreenQuad.Initialize(gDevice, gDeviceContext);
	CreateFullScreenQuad();

	killCountQuad.Initialize(gDevice, gDeviceContext);
	CreateKillCountQuad();

	waveCountQuad.Initialize(gDevice, gDeviceContext);
	CreateWaveCountQuad();
	
	waveCompleteQuad.Initialize(gDevice, gDeviceContext);
	CreateWaveCompleteQuad();
}

void MeshManager::Release()
{
	for (size_t i = 0; i < gameMeshes->size(); i++)
	{
		gameMeshes->at(i).Release();
	}
	for (size_t i = 0; i < sceneMeshes->size(); i++)
	{
		sceneMeshes->at(i).Release();
	}
	placeHolder.Release();
	placeHolderPlane.Release();
	quadTree->Release();
	fullScreenQuad.Release(); 
	killCountQuad.Release();
	waveCountQuad.Release();
	waveCompleteQuad.Release();
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




void MeshManager::CreateQuadTree()
{
	this->quadTree->Initialize(this->sceneMeshes, this->gDevice, this->gDeviceContext);
}

void MeshManager::GetMeshRenderInfo(MeshEnum * meshEnum, RenderInstructions * toRender)
{
	if (*meshEnum == MeshEnum::MAIN_CHARACTER)
		this->gameMeshes->at(0).GetMeshRenderInfo(toRender);

	else if (*meshEnum == MeshEnum::ENEMY_1)
		this->gameMeshes->at(1).GetMeshRenderInfo(toRender);
	else if (*meshEnum == MeshEnum::ENEMY_2)
		this->gameMeshes->at(2).GetMeshRenderInfo(toRender);
	else if (*meshEnum == MeshEnum::TRAP_BEAR)
	{
		this->gameMeshes->at(3).GetMeshRenderInfo(toRender);
	}
	else if (*meshEnum == MeshEnum::TRAP_FIRE)
		this->gameMeshes->at(4).GetMeshRenderInfo(toRender);
	else if (*meshEnum == MeshEnum::PROJECTILE_1)
		this->gameMeshes->at(5).GetMeshRenderInfo(toRender);
	else if (*meshEnum == MeshEnum::PICKUP_HEAL)
			toRender->materialID = 23;
	else if (*meshEnum == MeshEnum::PICKUP_WEAPON)
			toRender->materialID = 24;

	else if (*meshEnum == MeshEnum::PLACEHOLDER)
		this->GetPlaceHolderMeshInfo(toRender);
	


	else
	{
		
		this->gameMeshes->at(5).GetMeshRenderInfo(toRender);
	}

	//else
	//	this->placeHolder.GetMeshRenderInfo(toRender);


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


	(Float3)planeVerts[0].position = Float3(-200.0f, -0.1f, 200.0f);		//0
	planeVerts[0].uv.x = 0.0f;
	planeVerts[0].uv.y = 0.0f;
	(Float3)planeVerts[0].normal = Float3(0.0f, 1.0f, 0.0f);
	

	(Float3)planeVerts[1].position = Float3(200.0f, -0.1f, 200.0f);		//3
	planeVerts[1].uv.x = 1.0;
	planeVerts[1].uv.y = 0.0f;
	(Float3)planeVerts[1].normal = Float3(0.0f, 1.0f, 0.0f);


	(Float3)planeVerts[2].position = Float3(200.0f, -0.1f, -200.0f);		//5
	planeVerts[2].uv.x = 1.0f;
	planeVerts[2].uv.y = 1.0f;
	(Float3)planeVerts[2].normal = Float3(0.0f, 1.0f, 0.0f);


	(Float3)planeVerts[3].position = Float3(-200.0f, -0.1f, -200.0f);		//7
	planeVerts[3].uv.x = 0.0f;
	planeVerts[3].uv.y = 1.0f;
	(Float3)planeVerts[3].normal = Float3(0.0f, 1.0f, 0.0f);

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

void MeshManager::CreateKillCountQuad()
{
	Vertex planeVerts[4];

	planeVerts[0].position = Float3(-1.0f, 1.0f, 0.0f);		//0
	planeVerts[0].uv.x = 0.035f;
	planeVerts[0].uv.y = 1-0.577f;

	planeVerts[1].position = Float3(-0.5f, 1.0f, 0.0f);		//3
	planeVerts[1].uv.x = 0.062f;
	planeVerts[1].uv.y = 1-0.577f;
	

	planeVerts[2].position = Float3(-0.5f, 0.8f, 0.0f);		//5
	planeVerts[2].uv.x = 0.062f;
	planeVerts[2].uv.y = 1-0.525f;

	planeVerts[3].position = Float3(-1.0f, 0.8f, 0.0f);		//7
	planeVerts[3].uv.x = 0.035f;
	planeVerts[3].uv.y = 1-0.525f;

	UINT indices[6] =
	{
		0, 1, 2,
		0, 2, 3
	};

	this->killCountQuad.CreateVertexBuffer(planeVerts, 4, false);
	this->killCountQuad.CreateIndexBuffer(indices, 6, false);
}

void MeshManager::CreateWaveCountQuad()
{
	//wave Counter Quad for the wave numbers
	Vertex planeVerts[4];

	planeVerts[0].position = Float3(-1.0f, -0.8f, 0.0f);		//0
	planeVerts[0].uv.x = 0.083f;
	planeVerts[0].uv.y = 1 - 0.476f;

	planeVerts[1].position = Float3(-0.8f, -0.8f, 0.0f);		//3
	planeVerts[1].uv.x = 0.129f;
	planeVerts[1].uv.y = 1 - 0.476f;

	planeVerts[2].position = Float3(-0.8f, -1.0f, 0.0f);		//5
	planeVerts[2].uv.x = 0.129f;
	planeVerts[2].uv.y = 1 - 0.423f;
	
	planeVerts[3].position = Float3(-1.0f, -1.0f, 0.0f);		//7
	planeVerts[3].uv.x = 0.083f;
	planeVerts[3].uv.y = 1 - 0.423f;

	//offset.enemyOffsetX = 10;
	//offset.waveOffsetX = 10;



	UINT indices[6] =
	{
		0, 1, 2,
		0, 2, 3
	};

	this->waveCountQuad.CreateVertexBuffer(planeVerts, 4, false);
	this->waveCountQuad.CreateIndexBuffer(indices, 6, false);
}

void MeshManager::CreateWaveCompleteQuad()
{
	Vertex planeVerts[4];

	//planeVerts[0].position = Float3(
	//	(float)(2.0f * (float)(0.2863f*(float)WIN_WIDTH)) / (float)WIN_HEIGHT - 1.0f,
	//	(float)(2.0f * -((float)(0.2217f*(float)WIN_HEIGHT))) / (float)WIN_WIDTH + 1.0f,
	//	0.0f);		//0
	//planeVerts[0].uv.x = 0.0f;
	//planeVerts[0].uv.y = 0.0f;

	//planeVerts[1].position = Float3(
	//	(float)(2.0f * (float)(0.7075f*(float)WIN_WIDTH)) / (float)WIN_HEIGHT - 1.0f,
	//	(float)(2.0f * -((float)(0.2217f*(float)WIN_HEIGHT))) / (float)WIN_WIDTH + 1.0f,
	//	0.0f);		//1
	//planeVerts[1].uv.x = 1.0f;
	//planeVerts[1].uv.y = 0.0f;

	//planeVerts[2].position = Float3(
	//	(float)(2.0f * (float)(0.7075f*(float)WIN_WIDTH)) / (float)WIN_HEIGHT - 1.0f,
	//	(float)(2.0f * -((float)(0.3283f*(float)WIN_HEIGHT))) / (float)WIN_WIDTH + 1.0f,
	//	0.0f);			//2
	//planeVerts[2].uv.x = 1.0f;
	//planeVerts[2].uv.y = 1.0f;

	//planeVerts[3].position = Float3(
	//	(float)(2.0f * (float)(0.2863f*(float)WIN_WIDTH)) / (float)WIN_HEIGHT - 1.0f,
	//	(float)(2.0f * -((float)(0.3283f*(float)WIN_HEIGHT))) / (float)WIN_WIDTH + 1.0f,
	//	0.0f);			//3
	//planeVerts[3].uv.x = 0.0f;
	//planeVerts[3].uv.y = 1.0f;



	//offset.enemyOffsetX = 10;
	//offset.waveOffsetX = 10;


	//UINT indices[6] =
	//{
	//	0, 1, 2,
	//	0, 2, 3
	//};


	//planeVerts[0].position = Float3(-1.0f, -1.0f, 0.0f);		//0
	//planeVerts[0].uv.x = 0.0f;
	//planeVerts[0].uv.y = 1.0f;

	//planeVerts[1].position = Float3(-1.0f, 1.0f, 0.0f);		//3
	//planeVerts[1].uv.x = 0.0f;
	//planeVerts[1].uv.y = 0.0f;

	//planeVerts[2].position = Float3(1.0f, -1.0f, 0.0f);		//5
	//planeVerts[2].uv.x = 1.0f ;
	//planeVerts[2].uv.y = 1.0f ;

	//planeVerts[3].position = Float3(1.0f, 1.0f, 0.0f);		//7
	//planeVerts[3].uv.x	   = 1.0f;
	//planeVerts[3].uv.y	   = 0.0f;

	float offsetY = 0.7f;

	planeVerts[0].position = Float3(-0.3f, -0.05f + offsetY, 0.0f);		//0
	planeVerts[0].uv.x = 0.0f;
	planeVerts[0].uv.y = 1.0f;

	planeVerts[1].position = Float3(-0.3f, 0.05f + offsetY, 0.0f);		//3
	planeVerts[1].uv.x = 0.0f;
	planeVerts[1].uv.y = 0.0f;

	planeVerts[2].position = Float3( 0.3f, -0.05f + offsetY, 0.0f);		//5
	planeVerts[2].uv.x = 1.0f;
	planeVerts[2].uv.y = 1.0f;

	planeVerts[3].position = Float3(0.3f, 0.05f + offsetY, 0.0f);		//7
	planeVerts[3].uv.x = 1.0f;
	planeVerts[3].uv.y = 0.0f;




	UINT indices[6] =
	{
		0, 1, 2,
		1, 3, 2
	};

	this->waveCompleteQuad.CreateVertexBuffer(planeVerts, 4, false);
	this->waveCompleteQuad.CreateIndexBuffer(indices, 6, false);
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
void MeshManager::GetFullScreenQuadInfoUI(UITextures* uiEnum, RenderInstructions * toRender)
{
	if (*uiEnum == UITextures::HUD)
	{
		fullScreenQuad.GetMeshRenderInfo(toRender);
		toRender->materialID = 15;
	}
	else if (*uiEnum == UITextures::MENU)
	{
		fullScreenQuad.GetMeshRenderInfo(toRender);
		toRender->materialID = 16;
	}
	else if (*uiEnum == UITextures::GAMEOVER)
	{
		fullScreenQuad.GetMeshRenderInfo(toRender);
		toRender->materialID = 17;
	}
	else if (*uiEnum == UITextures::PAUSE)
	{
		fullScreenQuad.GetMeshRenderInfo(toRender);
		toRender->materialID = 18;
	}
	else if (*uiEnum == UITextures::CONTROLS)
	{
		fullScreenQuad.GetMeshRenderInfo(toRender);
		toRender->materialID = 19;
	}
	else if (*uiEnum == UITextures::WIN)
	{
		fullScreenQuad.GetMeshRenderInfo(toRender);
		toRender->materialID = 22;
	}
	if (*uiEnum == UITextures::NUMERATION)
	{
		killCountQuad.GetMeshRenderInfo(toRender);
		toRender->materialID = 21;
	}
	if (*uiEnum == UITextures::WAVECOUNTER)
	{
		waveCountQuad.GetMeshRenderInfo(toRender);
		toRender->materialID = 22;
	}
	else if (*uiEnum == UITextures::WAVECOMPLETE)
	{
		waveCompleteQuad.GetMeshRenderInfo(toRender);
		toRender->materialID = 25;
	}
	/*else if (*uiEnum == UITextures::NUMERATION)
	{
		fullScreenQuad.GetMeshRenderInfo(toRender);
		toRender->materialID = 15;
	}
	//else if (*uiEnum == UITextures::RESUMEPAUSE)
		toRender->materialID = 14;

	}*/

}

void MeshManager::GetKillCountQuadInfoHud(UITextures * uiEnum, RenderInstructions * toRender)
{
	//if (*uiEnum == UITextures::NUMERATION)
	//{
	//	killCountQuad.GetMeshRenderInfo(toRender);
	//	toRender->materialID = 14;
	//}
}

void MeshManager::GetWaveCountQuadInfoHud(UITextures * uiEnum, RenderInstructions * toRender)
{
	/*if (*uiEnum == UITextures::WAVECOUNTER)
	{
		waveCountQuad.GetMeshRenderInfo(toRender);
		toRender->materialID = 15;
	}*/
}

#pragma endregion
