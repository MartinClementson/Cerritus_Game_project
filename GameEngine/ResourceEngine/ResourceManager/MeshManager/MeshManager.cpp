#include "MeshManager.h"




MeshManager::MeshManager()
{
	this->gameMeshes		 = new std::vector<Mesh>;
	this->animatedMeshes	 = new std::vector<Mesh>;
	this->blendShapeMeshes   = new std::vector<Mesh*>;
}
MeshManager::~MeshManager()
{
	delete gameMeshes;
	delete animatedMeshes;
	for (size_t i = 0; i < blendShapeMeshes->size(); i++)
	{
		delete blendShapeMeshes->at(i);
	}
	delete blendShapeMeshes;	
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

	//Create three blendshapes
	for (int i = 0; i < 2; i++) //if you change amount, change it in release function as well
		CreatePlaceHolderBlendShape(); 

	animatedMeshes->push_back(Mesh());
	animatedMeshes->at(0).Initialize(gDevice,gDeviceContext);
	unsigned int tempNrFrames[1] = {2};
	float tempNrTime[1]			 = { 5.0f };

	Vertex cubeVerts[8];

	cubeVerts[0].position = Float3(-0.5, 2.5, 0.5);		//0
	cubeVerts[1].position = Float3(-0.5, 0.0, 0.5);		//1
	cubeVerts[2].position = Float3(0.5, 0.0, 0.5);		//2
	cubeVerts[3].position = Float3(0.5, 2.5, 0.5);		//3
	cubeVerts[4].position = Float3(0.5, 0.0, -0.5);		//4
	cubeVerts[5].position = Float3(0.5, 2.5, -0.5);		//5
	cubeVerts[6].position = Float3(-0.5, 0.0, -0.5);		//6
	cubeVerts[7].position = Float3(-0.5, 2.5, -0.5);		//7
	animatedMeshes->at(0).CreateAnimatedMesh(cubeVerts,8,1, tempNrFrames, tempNrTime);
#pragma region Create structured buffers for the animations
	HRESULT hr;
	for (int j = 0; j < animatedMeshes->size(); j++)
	{
		for (size_t i = 0; i < animatedMeshes->at(j).animationCount; i++) // for every animation, make a bstructured buffer with all the frames in it (one frame = one mesh)
		{

			UINT bufferIndex = UINT(morphAnimStructuredBuffers.size() + i);

			ID3D11ShaderResourceView* temp;
			morphAnimStructuredBuffersSRV.push_back(temp);
			ID3D11Buffer* tempB;
			morphAnimStructuredBuffers.push_back(tempB);

			D3D11_BUFFER_DESC BufferDesc;
			ZeroMemory(&BufferDesc, sizeof(BufferDesc));
			BufferDesc.BindFlags			 = D3D11_BIND_SHADER_RESOURCE;
			BufferDesc.Usage				 = D3D11_USAGE_DYNAMIC;
			BufferDesc.CPUAccessFlags		 = D3D11_CPU_ACCESS_WRITE;
			BufferDesc.MiscFlags			 = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
			BufferDesc.ByteWidth			 = sizeof(BlendShapeVert) * (animatedMeshes->at(j).GetVertCount()) * (animatedMeshes->at(j).animations.at(i).numberOfFrames);
			BufferDesc.StructureByteStride   = sizeof(BlendShapeVert);

			if (FAILED(hr = gDevice->CreateBuffer(&BufferDesc, nullptr, &morphAnimStructuredBuffers.at(bufferIndex))))
				MessageBox(NULL, L"Failed to create blend shapes buffer", L"Error", MB_ICONERROR | MB_OK);


			D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
			srvDesc.Format					 = DXGI_FORMAT_UNKNOWN;
			srvDesc.ViewDimension			 = D3D11_SRV_DIMENSION_BUFFEREX;
			srvDesc.Buffer.ElementOffset	 = 0;
			srvDesc.Buffer.ElementWidth		 = sizeof(BlendShapeVert);
			srvDesc.Buffer.NumElements		 = animatedMeshes->at(j).GetVertCount() * animatedMeshes->at(j).animations.at(i).numberOfFrames;
			if (FAILED(hr = gDevice->CreateShaderResourceView(morphAnimStructuredBuffers.at(bufferIndex), &srvDesc, &morphAnimStructuredBuffersSRV.at(bufferIndex))))
				MessageBox(NULL, L"Failed to create blend shapes buffer", L"Error", MB_ICONERROR | MB_OK);
			//this->gDeviceContext->VSSetShaderResources(MORPHANIM_BUFFER_START_INDEX + j, 1, &blendShapeStructuredBuffersSRV[j]);
			//this->gDeviceContext->GSSetShaderResources(MORPHANIM_BUFFER_START_INDEX + j, 1, &blendShapeStructuredBuffersSRV[j]);
			animationBufferCount += 1;
		
	


#pragma region Map The buffers
			////////////////////////////////////////////////////////////////////////////////////////
			////////////////////////////////////////////////////////////////////////////////////////
			////Map morph anim structure
			BlendShapeVert* vertices = new BlendShapeVert[animatedMeshes->at(j).GetVertCount() * animatedMeshes->at(j).animations.at(i).numberOfFrames] ;
			unsigned int   amount = 0  ;

			for (size_t frame = 0; frame < animatedMeshes->at(j).animations.at(i).numberOfFrames; frame++) //put all the morph targets into one array
			{
				for (size_t verts = 0; verts < *blendShapeMeshes->at(frame)->GetMeshBlendShape().amount; verts++)
				{														   
					vertices[verts + frame * (*blendShapeMeshes->at(frame) -> GetMeshBlendShape().amount)] =  blendShapeMeshes->at(frame)->GetMeshBlendShape().BlendShapeVertArray[verts];
				}
				amount   += *blendShapeMeshes->at(frame)->GetMeshBlendShape().amount;
			}

			D3D11_MAPPED_SUBRESOURCE mapRes;
			HRESULT hr = S_OK;

			hr = gDeviceContext->Map(morphAnimStructuredBuffers.at(bufferIndex), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapRes);
			if (FAILED(hr))
				MessageBox(NULL, L"Failed to update blend shapes buffer", L"Error", MB_ICONERROR | MB_OK);

			memcpy(mapRes.pData, (void*)vertices, sizeof(BlendShapeVert) * amount);
			gDeviceContext		->Unmap(morphAnimStructuredBuffers.at(bufferIndex), 0);
			this->gDeviceContext->VSSetShaderResources(MORPHANIM_BUFFER_START_INDEX + j, 1, &morphAnimStructuredBuffersSRV.at(bufferIndex));
			delete vertices;
			////////////////////////////////////////////////////////////////////////////////////////
			////////////////////////////////////////////////////////////////////////////////////////
#pragma endregion
		}
	}


#pragma endregion
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
	
	for (size_t i = 0; i < animatedMeshes->size(); i++)
	{
		animatedMeshes->at(i).Release();
	}

	for (size_t i = 0; i < morphAnimStructuredBuffersSRV.size(); i++)
	{
			morphAnimStructuredBuffersSRV.at(i)->Release();
			morphAnimStructuredBuffers.at(i)->Release();
	}
	
	for (int i = 0; i < blendShapeMeshes->size(); i++)
		this->blendShapeMeshes->at(i)->Release();

}

void MeshManager::AddMesh(bool hasSkeleton, unsigned int skeletonID, int materialID, unsigned int vertexCount, UINT indexCount, std::vector<Vertex> vertices, std::vector<AnimVert> aniVertices, std::vector<UINT> indices)
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


//int MeshManager::GetMaterialID(unsigned int index)
//{
//	return gameMeshes->at(index);
//}

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
	else if (*meshEnum == MeshEnum::LEVEL_1)
	{
		this->gameMeshes->at(4).SetMaterialID(3); //FULLÖSNING
		this->gameMeshes->at(4).GetMeshRenderInfo(toRender);
	}
	else if (*meshEnum == MeshEnum::LEVEL_2)
		this->gameMeshes->at(5).GetMeshRenderInfo(toRender);
	else if (*meshEnum == MeshEnum::LEVEL_3)
		this->gameMeshes->at(7).GetMeshRenderInfo(toRender);
	else if (*meshEnum == MeshEnum::LEVEL_4)
		this->gameMeshes->at(8).GetMeshRenderInfo(toRender);
	else if (*meshEnum == MeshEnum::PROJECTILE_1)
		this->gameMeshes->at(9).GetMeshRenderInfo(toRender);

	else
	{
		this->gameMeshes->at(6).GetMeshRenderInfo(toRender);
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
	
	this->placeHolder.CreateVertexBuffer(cubeVerts, 8);
	this->placeHolder.CreateIndexBuffer(indices, 36);


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


	

	this->placeHolderPlane.CreateVertexBuffer(planeVerts, 4);
	this->placeHolderPlane.CreateIndexBuffer(indices, 6); 
	
}

void MeshManager::CreatePlaceHolderBlendShape()
{
	size_t blendShapeIndex = blendShapeMeshes->size();
	static float x = 1.0f;
	static float y = 1.0f;
	
		BlendShapeVert cubeVerts[8];

		cubeVerts[0].position = Float3(-x, 2.5, 0.5);			//0
		cubeVerts[1].position = Float3(-x, 0.0, 0.5);			//1
		cubeVerts[2].position = Float3( x, 0.0, 0.5);			//2
		cubeVerts[3].position = Float3( x, 2.5, 0.5);			//3
		cubeVerts[4].position = Float3( x, 0.0, -0.5);			//4
		cubeVerts[5].position = Float3( x, 2.5, -0.5);			//5
		cubeVerts[6].position = Float3(-x, 0.0, -0.5);			//6
		cubeVerts[7].position = Float3(-x, 2.5, -0.5);			//7





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

		blendShapeMeshes->push_back(new Mesh());
		this->blendShapeMeshes->at(blendShapeIndex)->Initialize(this->gDevice,this->gDeviceContext);
		this->blendShapeMeshes->at(blendShapeIndex)->CreateBlendShape(cubeVerts, 8);
		/*this->blendShapeMeshes.at(blendShapeMeshes.size() - 1).CreateVertexBuffer(cubeVerts, 8);
		this->blendShapeMeshes.at(blendShapeMeshes.size() - 1).CreateIndexBuffer (indices,  36);*/

		x				+= 5.0f; 
		blendShapeIndex += 1;
	
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




	this->fullScreenQuad.CreateVertexBuffer(planeVerts, 4);
	this->fullScreenQuad.CreateIndexBuffer(indices, 6);


}


void MeshManager::GetPlaceHolderMeshInfo(RenderInstructions * toRender)
{
	for (UINT i = 0; i < morphAnimStructuredBuffersSRV.size(); i++)
		this->gDeviceContext->VSSetShaderResources(MORPHANIM_BUFFER_START_INDEX + i, 1, &morphAnimStructuredBuffersSRV.at(i));
	

	
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
		toRender->materialID = 9;
		//fullScreenQuad.GetMaterialID();
	}
	else if (*uiEnum == UITextures::MENU)
	{
		fullScreenQuad.GetMeshRenderInfo(toRender);
		toRender->materialID = 10;
	}
	else if (*uiEnum == UITextures::GAMEOVER)
	{
		fullScreenQuad.GetMeshRenderInfo(toRender);
		toRender->materialID = 11;
	}
	else if (*uiEnum == UITextures::PAUSE)
	{
		fullScreenQuad.GetMeshRenderInfo(toRender);
		toRender->materialID = 12;
	}
	else if (*uiEnum == UITextures::EXITMENU)
	{
		fullScreenQuad.GetMeshRenderInfo(toRender);
		toRender->materialID = 13;
	}
	else if (*uiEnum == UITextures::RESTARTMENU)
	{
		fullScreenQuad.GetMeshRenderInfo(toRender);
		toRender->materialID = 14;
	}
	else if (*uiEnum == UITextures::CONTROLSBUTTONMENU)
	{
		fullScreenQuad.GetMeshRenderInfo(toRender);
		toRender->materialID = 15;
	}
	else if (*uiEnum == UITextures::CONTROLS)
	{
		fullScreenQuad.GetMeshRenderInfo(toRender);
		toRender->materialID = 16;
	}
	//else if (*uiEnum == UITextures::RESUMEPAUSE)
	//{
	//	fullScreenQuad.GetMeshRenderInfo(toRender);
	//	toRender->materialID = 14;
	//}
	//else if (*uiEnum == UITextures::EXITPAUSE)
	//{
	//	fullScreenQuad.GetMeshRenderInfo(toRender);
	//	toRender->materialID = 15;
	//}
	//fullScreenQuad.GetMeshRenderInfo(toRender);
	//toRender->materialID = 6;
	//toRender->materialID = 7;
//	toRender->materialID = 8;
//	toRender->materialID = 6; //temp
}
#pragma endregion
