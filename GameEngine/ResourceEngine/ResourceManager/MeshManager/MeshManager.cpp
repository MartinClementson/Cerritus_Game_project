#include "MeshManager.h"




MeshManager::MeshManager()
{
	this->gameMeshes		 = new std::vector<Mesh>;
	this->animatedMeshes	 = new std::vector<Mesh>;
	this->blendShapeMeshes   = new std::vector<std::vector<Mesh*>>;
}
MeshManager::~MeshManager()
{
	delete gameMeshes;
	delete animatedMeshes;

	for (size_t i = 0; i < blendShapeMeshes->size(); i++)
		for (size_t j = 0; j < blendShapeMeshes->at(i).size(); j++)
			delete blendShapeMeshes->at(i).at(j);

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
	//for (int i = 0; i < 2; i++) //if you change amount, change it in release function as well
		//CreatePlaceHolderBlendShape(); 

	//animatedMeshes->push_back(Mesh());
	//animatedMeshes->at(0).Initialize(gDevice,gDeviceContext);
	CreatePlaceHolderAnimation();

	unsigned int tempNrFrames[1] = {2};
	float tempNrTime[1]			 = { 5.0f };

	Vertex cubeVerts[8];

	cubeVerts[0].position = Float3(-0.5, 2.5, 0.5);		//0
	cubeVerts[1].position = Float3(-0.5, 0.0, 0.5);		//1
	cubeVerts[2].position = Float3(0.5, 0.0, 0.5);		//2
	cubeVerts[3].position = Float3(0.5, 2.5, 0.5);		//3
	cubeVerts[4].position = Float3(0.5, 0.0, -0.5);		//4
	cubeVerts[5].position = Float3(0.5, 2.5, -0.5);		//5
	cubeVerts[6].position = Float3(-0.5, 0.0, -0.5);	//6
	cubeVerts[7].position = Float3(-0.5, 2.5, -0.5);	//7
	//animatedMeshes->at(0).CreateAnimatedMesh(cubeVerts,8,1, tempNrFrames, tempNrTime);
//#pragma region Create structured buffers for the animations
//	HRESULT hr;
//	for (int j = 0; j < animatedMeshes->size(); j++)
//	{
//		for (size_t i = 0; i < animatedMeshes->at(j).animationCount; i++) // for every animation, make a bstructured buffer with all the frames in it (one frame = one mesh)
//		{
//
//			UINT bufferIndex = UINT(morphAnimStructuredBuffers.size() + i);
//
//			ID3D11ShaderResourceView* temp;
//			morphAnimStructuredBuffersSRV.push_back(temp);
//			ID3D11Buffer* tempB;
//			morphAnimStructuredBuffers.push_back(tempB);
//
//			D3D11_BUFFER_DESC BufferDesc;
//			ZeroMemory(&BufferDesc, sizeof(BufferDesc));
//			BufferDesc.BindFlags			 = D3D11_BIND_SHADER_RESOURCE;
//			BufferDesc.Usage				 = D3D11_USAGE_DYNAMIC;
//			BufferDesc.CPUAccessFlags		 = D3D11_CPU_ACCESS_WRITE;
//			BufferDesc.MiscFlags			 = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
//			BufferDesc.ByteWidth			 = sizeof(BlendShapeVert) * (animatedMeshes->at(j).GetVertCount()) * (animatedMeshes->at(j).animations.at(i).numberOfFrames);
//			BufferDesc.StructureByteStride   = sizeof(BlendShapeVert);
//
//			if (FAILED(hr = gDevice->CreateBuffer(&BufferDesc, nullptr, &morphAnimStructuredBuffers.at(bufferIndex))))
//				MessageBox(NULL, L"Failed to create blend shapes buffer", L"Error", MB_ICONERROR | MB_OK);
//
//
//			D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
//			srvDesc.Format					 = DXGI_FORMAT_UNKNOWN;
//			srvDesc.ViewDimension			 = D3D11_SRV_DIMENSION_BUFFEREX;
//			srvDesc.Buffer.ElementOffset	 = 0;
//			srvDesc.Buffer.ElementWidth		 = sizeof(BlendShapeVert);
//			srvDesc.Buffer.NumElements		 = animatedMeshes->at(j).GetVertCount() * animatedMeshes->at(j).animations.at(i).numberOfFrames;
//			if (FAILED(hr = gDevice->CreateShaderResourceView(morphAnimStructuredBuffers.at(bufferIndex), &srvDesc, &morphAnimStructuredBuffersSRV.at(bufferIndex))))
//				MessageBox(NULL, L"Failed to create blend shapes buffer", L"Error", MB_ICONERROR | MB_OK);
//			//this->gDeviceContext->VSSetShaderResources(MORPHANIM_BUFFER_START_INDEX + j, 1, &blendShapeStructuredBuffersSRV[j]);
//			//this->gDeviceContext->GSSetShaderResources(MORPHANIM_BUFFER_START_INDEX + j, 1, &blendShapeStructuredBuffersSRV[j]);
//			animationBufferCount += 1;
//		
//	
//
//
//#pragma region Map The buffers
//			////////////////////////////////////////////////////////////////////////////////////////
//			////////////////////////////////////////////////////////////////////////////////////////
//			////Map morph anim structure
//			BlendShapeVert* vertices = new BlendShapeVert[animatedMeshes->at(j).GetVertCount() * animatedMeshes->at(j).animations.at(i).numberOfFrames] ;
//			unsigned int   amount = 0  ;
//
//			for (size_t frame = 0; frame < animatedMeshes->at(j).animations.at(i).numberOfFrames; frame++) //put all the morph targets into one array
//			{
//				for (size_t verts = 0; verts < *blendShapeMeshes->at(frame)->GetMeshBlendShape().amount; verts++)
//				{														   
//					vertices[verts + frame * (*blendShapeMeshes->at(frame) -> GetMeshBlendShape().amount)] =  blendShapeMeshes->at(frame)->GetMeshBlendShape().BlendShapeVertArray[verts];
//				}
//				amount   += *blendShapeMeshes->at(frame)->GetMeshBlendShape().amount;
//			}
//
//			D3D11_MAPPED_SUBRESOURCE mapRes;
//			HRESULT hr = S_OK;
//
//			hr = gDeviceContext->Map(morphAnimStructuredBuffers.at(bufferIndex), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapRes);
//			if (FAILED(hr))
//				MessageBox(NULL, L"Failed to update blend shapes buffer", L"Error", MB_ICONERROR | MB_OK);
//
//			memcpy(mapRes.pData, (void*)vertices, sizeof(BlendShapeVert) * amount);
//			gDeviceContext		->Unmap(morphAnimStructuredBuffers.at(bufferIndex), 0);
//			this->gDeviceContext->VSSetShaderResources(MORPHANIM_BUFFER_START_INDEX + j, 1, &morphAnimStructuredBuffersSRV.at(bufferIndex));
//			delete vertices;
//			////////////////////////////////////////////////////////////////////////////////////////
//			////////////////////////////////////////////////////////////////////////////////////////
//#pragma endregion
//		}
//	}


#pragma endregion
}

#pragma region temporary hiding
void MeshManager::Release()
{
	for (size_t i = 0; i < gameMeshes->size(); i++)
		gameMeshes->at(i).Release();
	
	placeHolder.Release();
	placeHolderPlane.Release();
	fullScreenQuad.Release();
	
	for (size_t i = 0; i < animatedMeshes->size(); i++)
		animatedMeshes->at(i).Release();
	

	for (size_t i = 0; i < morphAnimStructuredBuffersSRV.size(); i++)
	{
			morphAnimStructuredBuffersSRV.at(i)->Release();
			morphAnimStructuredBuffers   .at(i)->Release();
			animFrameStructuredBuffersSRV.at(i)->Release();
			animFrameStructuredBuffers   .at(i)->Release();
	}
	


	for (size_t i = 0; i < blendShapeMeshes->size(); i++)
		for (size_t j = 0; j < blendShapeMeshes->at(i).size(); j++)
			 blendShapeMeshes->at(i).at(j)->Release();
		
	

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
#pragma endregion

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

Mesh* MeshManager::CreatePlaceHolderBlendShape()
{
	
	static float x = 10.0f;

	
		BlendShapeVert cubeVerts[8];
		if (blendShapeMeshes->size() < 1)
		{

		cubeVerts[0].position = Float3(-x, 2.5, 0.5);			//0
		cubeVerts[1].position = Float3(-x, 0.0, 0.5);			//1
		cubeVerts[2].position = Float3( x, 0.0, 0.5);			//2
		cubeVerts[3].position = Float3( x, 2.5, 0.5);			//3
		cubeVerts[4].position = Float3( x, 0.0, -0.5);			//4
		cubeVerts[5].position = Float3( x, 2.5, -0.5);			//5
		cubeVerts[6].position = Float3(-x, 0.0, -0.5);			//6
		cubeVerts[7].position = Float3(-x, 2.5, -0.5);			//7
		}
		else
		{
			cubeVerts[0].position = Float3(-1, x, 0.5);			//0
			cubeVerts[1].position = Float3(-1, 0.0, 0.5);			//1
			cubeVerts[2].position = Float3( 1, 0.0, 0.5);			//2
			cubeVerts[3].position = Float3( 1, x, 0.5);			//3
			cubeVerts[4].position = Float3( 1, 0.0, -0.5);			//4
			cubeVerts[5].position = Float3( 1, x, -0.5);			//5
			cubeVerts[6].position = Float3(-1, 0.0, -0.5);			//6
			cubeVerts[7].position = Float3(-1, x, -0.5);			//7

			x				+= 10.0f; 
		}

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
		Mesh* toReturn = new Mesh();
		toReturn->Initialize(gDevice, gDeviceContext);
		toReturn->CreateBlendShape(cubeVerts, 8);
		

	
		return toReturn;
}

Mesh* MeshManager::CreateBlendShape(BlendShapeVert * vertices, unsigned int amount)
{
	Mesh* toReturn = new Mesh();
	toReturn->Initialize(gDevice, gDeviceContext);
	toReturn->CreateBlendShape(vertices, amount);
	
	return toReturn;

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
	{
		this->gDeviceContext->VSSetShaderResources(MORPHANIM_BUFFER_START_INDEX + i * 2   , 1, &morphAnimStructuredBuffersSRV.at(i)); //animation data
		this->gDeviceContext->VSSetShaderResources(MORPHANIM_BUFFER_START_INDEX + i * 2 +1, 1, &animFrameStructuredBuffersSRV.at(i)); //Frame data
	
	}

	
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



void MeshManager::CreatePlaceHolderAnimation()
{
	std::vector<Vertex> cubeVerts; //source
#pragma region first animation
	std::vector<BlendShapeVert> shapeOne;
	std::vector<BlendShapeVert> shapeTwo;
	std::vector<BlendShapeVert> shapeThree;
	for (size_t i = 0; i < 8; i++)
	{
		cubeVerts.push_back(Vertex());
		shapeOne .push_back(BlendShapeVert());
		shapeTwo .push_back(BlendShapeVert());
		shapeThree.push_back(BlendShapeVert());
	}
	cubeVerts.at(0).position = Float3(-0.5, 2.5, 0.5);		//0
	cubeVerts.at(1).position = Float3(-0.5, 0.0, 0.5);		//1
	cubeVerts.at(2).position = Float3( 0.5, 0.0, 0.5);		//2
	cubeVerts.at(3).position = Float3( 0.5, 2.5, 0.5);		//3
	cubeVerts.at(4).position = Float3( 0.5, 0.0, -0.5);		//4
	cubeVerts.at(5).position = Float3( 0.5, 2.5, -0.5);		//5
	cubeVerts.at(6).position = Float3(-0.5, 0.0, -0.5);	    //6
	cubeVerts.at(7).position = Float3(-0.5, 2.5, -0.5);	    //7

	
	shapeOne.at(0).position = Float3(-0.5, 2.5,  10.0f);	//0
	shapeOne.at(1).position = Float3(-0.5, 0.0,  10.0f);	//1
	shapeOne.at(2).position = Float3(0.5, 0.0,   10.0f);	//2
	shapeOne.at(3).position = Float3(0.5, 2.5,   10.0f);	//3
	shapeOne.at(4).position = Float3(0.5, 0.0,  -10.0f);	//4
	shapeOne.at(5).position = Float3(0.5, 2.5,  -10.0f);	//5
	shapeOne.at(6).position = Float3(-0.5, 0.0, -10.0f);	//6
	shapeOne.at(7).position = Float3(-0.5, 2.5, -10.0f);   	//7

	
	shapeTwo.at(0).position = Float3(-0.5f, 10.0,  0.5);	//0
	shapeTwo.at(1).position = Float3(-0.5f, 0.0,   0.5);	//1
	shapeTwo.at(2).position = Float3( 0.5f, 0.0,   0.5);	//2
	shapeTwo.at(3).position = Float3( 0.5f, 10.0,  0.5);	//3
	shapeTwo.at(4).position = Float3( 0.5f, 0.0,  -0.5);	//4
	shapeTwo.at(5).position = Float3( 0.5f, 10.0, -0.5);	//5
	shapeTwo.at(6).position = Float3(-0.5f, 0.0,  -0.5);	//6
	shapeTwo.at(7).position = Float3(-0.5f, 10.0, -0.5);	//7


	shapeThree.at(0).position = Float3(-10.0f, 1.0,  0.25);	//0
	shapeThree.at(1).position = Float3(-10.0f, 0.0,  0.25);	//1
	shapeThree.at(2).position = Float3( 10.0f, 0.0,  0.25);	//2
	shapeThree.at(3).position = Float3( 10.0f, 1.0,  0.25);	//3
	shapeThree.at(4).position = Float3( 10.0f, 0.0, -0.25);	//4
	shapeThree.at(5).position = Float3( 10.0f, 1.0, -0.25);	//5
	shapeThree.at(6).position = Float3(-10.0f, 0.0, -0.25);	//6
	shapeThree.at(7).position = Float3(-10.0f, 1.0, -0.25);	//7




	std::vector<AnimationInfo> animations;
	animations.push_back(AnimationInfo());
	animations.at(0).animationTime = 10.0f;
	animations.at(0).numberOfFrames = 3;
	animations.at(0).meshesPerFrame.push_back(shapeOne);
	animations.at(0).meshesPerFrame.push_back(shapeTwo);
	animations.at(0).meshesPerFrame.push_back(shapeThree);

	animations.at(0).frames.push_back(FrameData(1 ,0.35f));
	animations.at(0).frames.push_back(FrameData(2 ,0.70f));
	animations.at(0).frames.push_back(FrameData(3 , 1.0f));
#pragma endregion














#pragma region second animation

	std::vector<BlendShapeVert> s_shapeOne;
	std::vector<BlendShapeVert> s_shapeTwo;
	std::vector<BlendShapeVert> s_shapeThree;
	for (size_t i = 0; i < 8; i++)
	{
		
		s_shapeOne.push_back(BlendShapeVert());
		s_shapeTwo.push_back(BlendShapeVert());
		s_shapeThree.push_back(BlendShapeVert());
	}


	s_shapeOne.at(0).position = Float3(-5.0, 2.5,  5.0);		//0
	s_shapeOne.at(1).position = Float3(-5.0, 0.0,  5.0);		//1
	s_shapeOne.at(2).position = Float3( 5.0, 0.0,  5.0);		//2
	s_shapeOne.at(3).position = Float3( 5.0, 2.5,  5.0);		//3
	s_shapeOne.at(4).position = Float3( 5.0, 0.0, -5.0);		//4
	s_shapeOne.at(5).position = Float3( 5.0, 2.5, -5.0);		//5
	s_shapeOne.at(6).position = Float3(-5.0, 0.0, -5.0);	    //6
	s_shapeOne.at(7).position = Float3(-5.0, 2.5, -5.0);	     //7


	s_shapeTwo.at(0).position = Float3(-0.2, 2.5, 5.0);   //0
	s_shapeTwo.at(1).position = Float3(-0.2, 0.0, 5.0);   //1
	s_shapeTwo.at(2).position = Float3( 0.2, 0.0, 5.0);   //2
	s_shapeTwo.at(3).position = Float3( 0.2, 2.5, 5.0);   //3
	s_shapeTwo.at(4).position = Float3( 0.2, 0.0, -5.0);  //4
	s_shapeTwo.at(5).position = Float3( 0.2, 2.5, -5.0);   //5
	s_shapeTwo.at(6).position = Float3(-0.2, 0.0, -5.0);  //6
	s_shapeTwo.at(7).position = Float3(-0.2, 2.5, -5.0);  //7


	s_shapeThree.at(0).position = Float3(-5.0, 2.5,  0.2);	//0
	s_shapeThree.at(1).position = Float3(-5.0, 0.0,  0.2);	//1
	s_shapeThree.at(2).position = Float3(5.0, 0.0,   0.2);    // 2
	s_shapeThree.at(3).position = Float3(5.0, 2.5,   0.2);	 // 3
	s_shapeThree.at(4).position = Float3(5.0, 0.0,  -0.2);	//4
	s_shapeThree.at(5).position = Float3(5.0, 2.5,  -0.2);	//5
	s_shapeThree.at(6).position = Float3(-5.0, 0.0, -0.2);	//6
	s_shapeThree.at(7).position = Float3(-5.0, 2.5, -0.2);	//7

	animations.push_back(AnimationInfo());
	animations.at(1).animationTime = 10.0f;
	animations.at(1).numberOfFrames = 3;
	animations.at(1).meshesPerFrame.push_back(s_shapeOne);
	animations.at(1).meshesPerFrame.push_back(s_shapeTwo);
	animations.at(1).meshesPerFrame.push_back(s_shapeThree);
				  
	animations.at(1).frames.push_back(FrameData(1, 0.35f));
	animations.at(1).frames.push_back(FrameData(2, 0.70f));
	animations.at(1).frames.push_back(FrameData(3, 1.0f));

#pragma endregion

	



#pragma region third animation

	std::vector<BlendShapeVert> t_shapeOne;
	std::vector<BlendShapeVert> t_shapeTwo;
	std::vector<BlendShapeVert> t_shapeThree;
	for (size_t i = 0; i < 8; i++)
	{

		t_shapeOne.push_back(BlendShapeVert());
		t_shapeTwo.push_back(BlendShapeVert());
		t_shapeThree.push_back(BlendShapeVert());
	}


	t_shapeOne.at(0).position = Float3(10.0, 2.5, 20.0);		//0
	t_shapeOne.at(1).position = Float3(10.0, 0.0, 20.0);		//1
	t_shapeOne.at(2).position = Float3(20.0, 0.0, 20.0);		//2
	t_shapeOne.at(3).position = Float3(20.0, 2.5, 20.0);		//3
	t_shapeOne.at(4).position = Float3(20.0, 0.0, 10.0);		//4
	t_shapeOne.at(5).position = Float3(20.0, 2.5, 10.0);		//5
	t_shapeOne.at(6).position = Float3(10.0, 0.0, 10.0);	    //6
	t_shapeOne.at(7).position = Float3(10.0, 2.5, 10.0);	     //7


	t_shapeTwo.at(0).position = Float3(10.0, 20.5, 20.0);  //0
	t_shapeTwo.at(1).position = Float3(10.0, 10.0, 20.0);  //1
	t_shapeTwo.at(2).position = Float3(20.0, 10.0, 20.0); //2
	t_shapeTwo.at(3).position = Float3(20.0, 20.5, 20.0); //3
	t_shapeTwo.at(4).position = Float3(20.0, 10.0, 10.0); //4
	t_shapeTwo.at(5).position = Float3(20.0, 20.5, 10.0);  //5
	t_shapeTwo.at(6).position = Float3(10.0, 10.0, 10.0);  //6
	t_shapeTwo.at(7).position = Float3(10.0, 20.5, 10.0);  //7


	t_shapeThree.at(0).position = Float3(-0.5, 2.5, -10);			//0
	t_shapeThree.at(1).position = Float3(-0.5, 0.0,  -10);			//1
	t_shapeThree.at(2).position = Float3(0.5, 0.0,   -10);		  // 2
	t_shapeThree.at(3).position = Float3(0.5, 2.5,   -10);		 // 3
	t_shapeThree.at(4).position = Float3(0.5, 0.0,  -9.0);		//4
	t_shapeThree.at(5).position = Float3(0.5, 2.5,  -9.0);		//5
	t_shapeThree.at(6).position = Float3(-0.5, 0.0, -9.0);		//6
	t_shapeThree.at(7).position = Float3(-0.5, 2.5, -9.0);		//7
		
	animations.push_back(AnimationInfo());
	animations.at(2).animationTime = 10.0f;
	animations.at(2).numberOfFrames = 3;
	animations.at(2).meshesPerFrame.push_back(t_shapeOne);
	animations.at(2).meshesPerFrame.push_back(t_shapeTwo);
	animations.at(2).meshesPerFrame.push_back(t_shapeThree);
				  
	animations.at(2).frames.push_back(FrameData(1, 0.35f));
	animations.at(2).frames.push_back(FrameData(2, 0.40f));
	animations.at(2).frames.push_back(FrameData(3, 1.0f));

#pragma endregion

	CreateAnimationFromMeshes(cubeVerts, animations);


}
void MeshManager::CreateAnimationFromMeshes(std::vector<Vertex> sourceMesh, std::vector<AnimationInfo> animations)
{

#pragma region Create the mesh objects for the animation
	animatedMeshes->push_back(Mesh(gDevice,gDeviceContext));		   // create the new sourceMesh

	size_t meshIndex = animatedMeshes->size() - 1;
	animatedMeshes->at(meshIndex).CreateAnimatedMesh(sourceMesh.data(), (unsigned int)sourceMesh.size(), &animations);

	for (size_t i = 0; i < animations.size(); i++)					   //loop through all the animations
	{																   
		blendShapeMeshes->push_back(std::vector<Mesh*>());			   //for each animation, create a new array of meshes, each mesh represents a keyframe
		for (size_t j = 0;  j < animations.at(i).numberOfFrames;  j++) //for each frame, create a blendshape mesh
		{
			Mesh* newShape = CreateBlendShape(animations.at(i).meshesPerFrame.at(j).data(),(unsigned int) animations.at(i).meshesPerFrame.at(j).size());
			blendShapeMeshes->at(blendShapeMeshes->size() - 1).push_back(newShape);
		}
	}
#pragma endregion

#pragma region Create structured buffers for the animations
	HRESULT hr;
	
		for (size_t i = 0; i < animations.size(); i++) // for every animation, make a structured buffer with all the frames in it (one frame = one mesh)
		{
			////////////////////////////////////////////////////////////////////////////////////////
			////////////////////////////////////////////////////////////////////////////////////////
			////Create the animation buffer
			UINT bufferIndex = UINT(morphAnimStructuredBuffers.size()); // important that this is before the pushback.

			ID3D11ShaderResourceView* temp;
			morphAnimStructuredBuffersSRV.push_back(temp);
			ID3D11Buffer* tempB;
			morphAnimStructuredBuffers.push_back(tempB);

			ID3D11ShaderResourceView* tempC;
			animFrameStructuredBuffersSRV.push_back(tempC);
			ID3D11Buffer* tempD;
			animFrameStructuredBuffers.push_back(tempD);


			D3D11_BUFFER_DESC BufferDesc;
			ZeroMemory(&BufferDesc, sizeof(BufferDesc));
			BufferDesc.BindFlags			= D3D11_BIND_SHADER_RESOURCE;
			BufferDesc.Usage				= D3D11_USAGE_DYNAMIC;
			BufferDesc.CPUAccessFlags		= D3D11_CPU_ACCESS_WRITE;
			BufferDesc.MiscFlags			= D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
			BufferDesc.ByteWidth			= sizeof(BlendShapeVert) * (animatedMeshes->at(meshIndex).GetVertCount()) * (animatedMeshes->at(meshIndex).animations.at(i).numberOfFrames); //vertices * frames/meshes
			BufferDesc.StructureByteStride  = sizeof(BlendShapeVert);

			if (FAILED(hr = gDevice->CreateBuffer(&BufferDesc, nullptr, &morphAnimStructuredBuffers.at(bufferIndex))))
				MessageBox(NULL, L"Failed to create blend shapes buffer", L"Error", MB_ICONERROR | MB_OK);


			D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
			srvDesc.Format				 = DXGI_FORMAT_UNKNOWN;
			srvDesc.ViewDimension		 = D3D11_SRV_DIMENSION_BUFFEREX;
			srvDesc.Buffer.ElementOffset = 0;
			srvDesc.Buffer.ElementWidth	 = sizeof(BlendShapeVert);
			srvDesc.Buffer.NumElements	 = animatedMeshes->at( meshIndex ).GetVertCount() * animatedMeshes->at( meshIndex ).animations.at (i ).numberOfFrames; //vertices * frames/meshes
			if (FAILED(hr = gDevice->CreateShaderResourceView(morphAnimStructuredBuffers.at(bufferIndex), &srvDesc, &morphAnimStructuredBuffersSRV.at(bufferIndex))))
				MessageBox(NULL, L"Failed to create blend shapes buffer", L"Error", MB_ICONERROR | MB_OK);
		
			animationBufferCount += 1;

			////////////////////////////////////////////////////////////////////////////////////////
			////////////////////////////////////////////////////////////////////////////////////////
			////Create the frame buffer

			
		
			BufferDesc.ByteWidth			= sizeof(FrameData) * (animatedMeshes->at(meshIndex).animations.at(i).numberOfFrames); //frames/meshes
			BufferDesc.StructureByteStride  = sizeof(FrameData);

			if (FAILED(hr = gDevice->CreateBuffer(&BufferDesc, nullptr, &animFrameStructuredBuffers.at(bufferIndex))))
				MessageBox(NULL, L"Failed to create frame buffer", L"Error", MB_ICONERROR | MB_OK);


			
			srvDesc.Buffer.ElementWidth = sizeof(FrameData);
			srvDesc.Buffer.NumElements = animatedMeshes->at(meshIndex).animations.at(i).numberOfFrames;  //frames/meshes
			if (FAILED(hr = gDevice->CreateShaderResourceView(animFrameStructuredBuffers.at(bufferIndex), &srvDesc, &animFrameStructuredBuffersSRV.at(bufferIndex))))
				MessageBox(NULL, L"Failed to create blend shapes buffer", L"Error", MB_ICONERROR | MB_OK);




#pragma region Map The buffers
			////////////////////////////////////////////////////////////////////////////////////////
			////////////////////////////////////////////////////////////////////////////////////////
			////Map morph anim structure
			BlendShapeVert* vertices = new BlendShapeVert[animatedMeshes->at(meshIndex).GetVertCount() * animatedMeshes->at(meshIndex).animations.at(i).numberOfFrames];
			unsigned int   amount = 0;

			for (size_t frame = 0; frame < animatedMeshes->at(meshIndex).animations.at(i).numberOfFrames; frame++) //put all the morph targets into one array
			{
				for (size_t verts = 0; verts < *blendShapeMeshes->at(i).at(frame)->GetMeshBlendShape().amount; verts++)
				{
					vertices[verts + frame * (*blendShapeMeshes->at(i).at(frame)->GetMeshBlendShape().amount)] = blendShapeMeshes->at(i).at(frame)->GetMeshBlendShape().BlendShapeVertArray[verts];
				}
				amount += *blendShapeMeshes->at(i).at(frame)->GetMeshBlendShape().amount;
			}

			D3D11_MAPPED_SUBRESOURCE mapRes;
			HRESULT hr = S_OK;

			hr = gDeviceContext->Map(morphAnimStructuredBuffers.at(bufferIndex), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapRes);
			if (FAILED(hr))
				MessageBox(NULL, L"Failed to update blend shapes buffer", L"Error", MB_ICONERROR | MB_OK);

			memcpy(mapRes.pData, (void*)vertices, sizeof(BlendShapeVert) * amount);
			gDeviceContext->Unmap(morphAnimStructuredBuffers.at(bufferIndex), 0);
			this->gDeviceContext->VSSetShaderResources(MORPHANIM_BUFFER_START_INDEX + (UINT)bufferIndex * 2, 1, &morphAnimStructuredBuffersSRV.at(bufferIndex));
			delete vertices;
			////////////////////////////////////////////////////////////////////////////////////////
			////////////////////////////////////////////////////////////////////////////////////////


			////////////////////////////////////////////////////////////////////////////////////////
			////////////////////////////////////////////////////////////////////////////////////////
			////Map frame structure
			FrameData* frames = new FrameData[animatedMeshes->at(meshIndex).animations.at(i).numberOfFrames];
			

			for (size_t frame = 0; frame < animatedMeshes->at(meshIndex).animations.at(i).numberOfFrames; frame++) //put all the morph targets into one array
			{

				frames[frame].frameID = animatedMeshes->at(meshIndex).animations.at(i).frames.at(frame).frameID;
				frames[frame].time	  = animatedMeshes->at(meshIndex).animations.at(i).frames.at(frame).time;
				
			}

			

			hr = gDeviceContext->Map(animFrameStructuredBuffers.at(bufferIndex), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapRes);
			if (FAILED(hr))
				MessageBox(NULL, L"Failed to update frame buffer", L"Error", MB_ICONERROR | MB_OK);

			memcpy(mapRes.pData, (void*)frames, sizeof(BlendShapeVert) * amount);
			gDeviceContext->Unmap(animFrameStructuredBuffers.at(bufferIndex), 0);
			this->gDeviceContext->VSSetShaderResources(MORPHANIM_BUFFER_START_INDEX + (UINT)bufferIndex * 2 + 1, 1, &animFrameStructuredBuffersSRV.at(bufferIndex));
			delete frames;
			////////////////////////////////////////////////////////////////////////////////////////
			////////////////////////////////////////////////////////////////////////////////////////



#pragma endregion
		}
	
#pragma endregion

}
