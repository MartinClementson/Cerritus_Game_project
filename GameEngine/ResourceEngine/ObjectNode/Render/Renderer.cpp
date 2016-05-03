#include "Renderer.h"




Renderer::Renderer()
{
	this->sceneCam			= new Camera();
	this->resourceManager	= new ResourceManager();
	pointLightStruct		= new PointLightStruct();
	spotLightStruct			= new SpotLightStruct();
	dirLightStruct			= new DirLightStruct();
	

	//sceneLightArray->lightPosition		 = XMFLOAT4(0.0f, 30.0f, 0.0f, 1.0f); //Pos
	//sceneLightArray->lightLookAt		 = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);	//Direction
	//sceneLightArray->lightDiffuse		 = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);	//Color
	//sceneLightArray->SetMatrices(XM_PI*0.8f, 1.0f, 5.0f, 40.0f);
	//sceneLightArray->intensity			 = 1.0f;
}


Renderer::~Renderer()
{
	delete sceneCam;
	delete resourceManager;
	delete pointLightStruct;
	delete spotLightStruct;
	delete dirLightStruct;
}

void Renderer::Initialize(ID3D11Device *gDevice, ID3D11DeviceContext* gDeviceContext)
{
	this->gDeviceContext = gDeviceContext;
	this->gDevice = gDevice;
	this->lightmanager.Initialize();
	this->CreateBuffers();
	resourceManager->Initialize(gDevice, gDeviceContext);
	sceneCam->Initialize(gDevice, gDeviceContext);
	this->UpdateLightBuffer();
}
void Renderer::Release()
{
	lightmanager.Release();
	resourceManager->Release();
	sceneCam->Release();

	SAFE_RELEASE(worldBuffer);
	SAFE_RELEASE(cbufferPerFrame);
	
	SAFE_RELEASE(sampleBoolsBuffer);
	for (size_t i = 0; i < LIGHTBUFFER_AMOUNT; i++)
		SAFE_RELEASE(lightBuffers[i]);

	for (size_t i = 0; i < INSTANCED_BUFFER_AMOUNT; i++)
		SAFE_RELEASE(instancedBuffers[i]);

	
	SAFE_RELEASE(pointLightStructuredBuffer);
	SAFE_RELEASE(spotLightStructuredBuffer);
	SAFE_RELEASE(dirLightStructuredBuffer);

}

void Renderer::RenderBlurPass()
{
	this->resourceManager->SetShader(Shaders::BLUR_SHADER);
}

void Renderer::RenderFinalPass()
{

	RenderInstructions * objectInstruction;

	objectInstruction = this->resourceManager->GetFullScreenQuad();
	this->resourceManager->SetShader(Shaders::FINAL_SHADER);
	//MapLightBufferStructures();
	this->gDeviceContext->PSSetShaderResources(POINTLIGHTS_BUFFER_INDEX, 1, &pointLightStructuredBuffer);
	this->gDeviceContext->PSSetShaderResources(DIRLIGHTS_BUFFER_INDEX, 1, &dirLightStructuredBuffer);

	UINT32 vertexSize;

		vertexSize = sizeof(Vertex);

	UINT32 offset = 0;

	//an exception handling can be implemented here to handle if there is no buffer
	// to set. Then the handling can be to use a standard cube instead.

	this->gDeviceContext->IASetVertexBuffers(0, 1, &objectInstruction->vertexBuffer, &vertexSize, &offset);

	this->gDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	this->gDeviceContext->IASetIndexBuffer(objectInstruction->indexBuffer, DXGI_FORMAT_R32_UINT, 0);


	this->gDeviceContext->DrawIndexed((UINT)*objectInstruction->indexCount, 0, 0);

}

#pragma region Overloaded Render functions

//Render scene objects, mostly static stuff
void Renderer::Render(RenderInfoObject * object)
{
	RenderInstructions* renderObject;

	//Send the info of the object into the resource manager
	//The resource manager gathers all the rendering info and sends back a renderInstruction
	renderObject = this->resourceManager->GetRenderInfo(object);

	//Render with the given render instruction

	this->Render(renderObject);

	//RenderPlaceHolder(&object->position,&object->rotation);

	//RenderPlaceHolder(&object->position);

}


//Render 2d textures for the ui
void Renderer::Render(RenderInfoUI * object)
{

}

//Render an enemy mesh
void Renderer::Render(RenderInfoEnemy * object)
{
	RenderInstructions * objectInstruction;

	objectInstruction = this->resourceManager->GetRenderInfo(object);

	if (sceneCam->frustum->CheckCube(object->position.x, object->position.y, object->position.z, object->radius - 0.9f) == true)
	{
		Render(objectInstruction);
	}
}

void Renderer::RenderInstanced(RenderInfoEnemy* object, InstancedData* arrayData, unsigned int amount)
{
	RenderInstructions * objectInstruction;

	objectInstruction = this->resourceManager->GetRenderInfo(object);

	ID3D11Buffer* instanceBuffer;
	if (object->object == MeshEnum::ENEMY_1)
	{
		instanceBuffer = this->instancedBuffers[INSTANCED_WORLD];
		
	}





	//D3D11_MAPPED_SUBRESOURCE mapRes;
	//HRESULT hr = S_OK;

	//hr = gDeviceContext->Map(instancedBuffers[INSTANCED_WORLD], 0, D3D11_MAP_WRITE_DISCARD, 0, &mapRes);
	//if (FAILED(hr))
	//	MessageBox(NULL, L"Failed to update instanced buffer", L"Error", MB_ICONERROR | MB_OK);

	//memcpy(mapRes.pData, (void*)arrayData, sizeof(InstancedData)*amount);
	//gDeviceContext->Unmap(instancedBuffers[INSTANCED_WORLD], 0);



	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

	gDeviceContext->Map(instancedBuffers[INSTANCED_WORLD], 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);


	InstancedData* tempStructMatrices = (InstancedData*)mappedResource.pData;

	//*tempStructMatrices = *arrayData;
	memcpy(tempStructMatrices, (void*)arrayData, sizeof(InstancedData)*amount);


	gDeviceContext->Unmap(instancedBuffers[INSTANCED_WORLD], 0);





	RenderInstanced(objectInstruction, this->instancedBuffers[INSTANCED_WORLD], amount);


	//Reset the shaders to normal shaders for the next objects to rener
	if(this->resourceManager->IsGbufferPass())
		resourceManager->SetGbufferPass(true);
	if (this->resourceManager->IsShadowPass())
		resourceManager->SetShadowPass(true);
}


//Render the character, Update the camera to follow the position of the character
void Renderer::Render(RenderInfoChar * object)
{
	RenderInstructions * objectInstruction;
	
	objectInstruction = this->resourceManager->GetRenderInfo(object);

	//Update the camera view matrix!
	this->sceneCam->Updateview( object->position);
	this->UpdateCbufferPerFrame();

	Render(objectInstruction);

	

}


void Renderer::Render(RenderInfoTrap * object)
{
	RenderInstructions* renderObject;

	//Send the info of the object into the resource manager
	//The resource manager gathers all the rendering info and sends back a renderInstruction
	renderObject = this->resourceManager->GetRenderInfo(object);

	//Render with the given render instruction
	if (sceneCam->frustum->CheckCube(object->position.x, object->position.y, object->position.z, object->radius ) == true)
	{
		Render(renderObject);
	}
}


//Render the placeholder meshes
void Renderer::RenderPlaceHolder(XMFLOAT3* position)
{
	RenderInstructions * object;
	object = this->resourceManager->GetPlaceHolderMesh( *position );
	
	Render(object);
}

void Renderer::RenderPlaceHolder(XMFLOAT3 * position, XMFLOAT3 * rotation)
{
	RenderInstructions * object;
	object = this->resourceManager->GetPlaceHolderMesh(*position,*rotation);



	Render(object);


}
void Renderer::RenderPlaceHolderPlane()
{
	RenderInstructions * objectPlane;
	objectPlane = this->resourceManager->GetPlaceHolderPlane();
	Render(objectPlane);

}

#pragma endregion

void Renderer::SetMouseWorldPos(XMFLOAT4 position)
{
	this->mouseWorldPos = position;

}

void Renderer::GetInverseViewMatrix(XMMATRIX & matrix)
{
	matrix = XMLoadFloat4x4(&this->sceneCam->GetCameraMatrices()->camView);
	matrix = XMMatrixTranspose(matrix);
	XMVECTOR det = XMMatrixDeterminant(matrix);
	matrix = XMMatrixInverse(&det, matrix);
		
	
}

void Renderer::GetInverseProjectionMatrix(XMMATRIX & matrix)
{
	matrix = XMLoadFloat4x4(&this->sceneCam->GetCameraMatrices()->projection);
	matrix = XMMatrixTranspose(matrix); //Transpose to normal alignment.
	XMVECTOR det = XMMatrixDeterminant(matrix);
	matrix = XMMatrixInverse(&det, matrix);

}

//Private rendering call
void Renderer::Render(RenderInstructions * object)
{
	this->gDeviceContext->GSSetShaderResources(POINTLIGHTS_BUFFER_INDEX, 1, &pointLightStructuredBuffer);
	this->gDeviceContext->GSSetShaderResources(DIRLIGHTS_BUFFER_INDEX, 1, &dirLightStructuredBuffer);
	UpdateWorldBuffer(&object->worldBuffer);

#pragma region Check what vertex is to be used

	//We need to make sure that we use the right kind of vertex when rendering
	UINT32 vertexSize;
	
	if (*object->isAnimated		 == false)
		vertexSize = sizeof(Vertex);

	else if (*object->isAnimated == true)
		vertexSize = sizeof(AnimVert);

	else
		MessageBox(NULL, L"An object returned isAnimated as nullptr", L"Error in Renderer", MB_ICONERROR | MB_OK);
	
#pragma endregion


	UINT32 offset = 0;

	//an exception handling can be implemented here to handle if there is no buffer
	// to set. Then the handling can be to use a standard cube instead.

	this->gDeviceContext->IASetVertexBuffers(0, 1, &object->vertexBuffer, &vertexSize, &offset);
	
	this->gDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	this->gDeviceContext->IASetIndexBuffer(object->indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	


#pragma region Set the objects texture maps to the shader

	SampleBoolStruct sampleBools;
	if (object->diffuseMap != nullptr)
	{
		this->gDeviceContext->PSSetShaderResources(0, 1, &object->diffuseMap);
		sampleBools.diffuseMap = TRUE;
	}
	else
	{
		sampleBools.diffuseMap = FALSE;
	}

	if (object->normalMap != nullptr)
	{
		this->gDeviceContext->PSSetShaderResources(1, 1, &object->normalMap);
		sampleBools.normalMap = TRUE;
	}
	else
	{
		sampleBools.normalMap = FALSE;
	}
	
	if (object->specularMap != nullptr)
	{
		this->gDeviceContext->PSSetShaderResources(2, 1, &object->specularMap);
		sampleBools.specularMap = TRUE;
	}
	else
	{
		sampleBools.specularMap = FALSE;
	}

	if (object->glowMap != nullptr)
	{
		this->gDeviceContext->PSSetShaderResources(3, 1, &object->glowMap);
		sampleBools.glowMap = TRUE;
	}
	else
	{
		sampleBools.glowMap = FALSE;
	}

	this->UpdateSampleBoolsBuffer(&sampleBools);
#pragma endregion
	
	
	this->gDeviceContext->DrawIndexed((UINT)*object->indexCount, 0, 0);


}



void Renderer::RenderInstanced(RenderInstructions * object, ID3D11Buffer* instanceBuffer,unsigned int amount)
{
	this->gDeviceContext->GSSetShaderResources(POINTLIGHTS_BUFFER_INDEX, 1, &pointLightStructuredBuffer);
	this->gDeviceContext->GSSetShaderResources(DIRLIGHTS_BUFFER_INDEX, 1, &dirLightStructuredBuffer);
	

#pragma region Check what vertex is to be used

	//We need to make sure that we use the right kind of vertex when rendering
	UINT32 vertexSize[2];

	if (*object->isAnimated == false)
		vertexSize[0] = sizeof(Vertex);

	else if (*object->isAnimated == true)
		vertexSize[0] = sizeof(AnimVert);

	else
		MessageBox(NULL, L"An object returned isAnimated as nullptr", L"Error in Renderer", MB_ICONERROR | MB_OK);

#pragma endregion

	vertexSize[1] = sizeof(InstancedData);
	UINT32 offset[2] = { 0,0 };

	ID3D11Buffer* vbs[2] = { object->vertexBuffer,instanceBuffer };
	
	this->gDeviceContext->IASetVertexBuffers(0, 2 ,vbs, vertexSize, offset);
	this->gDeviceContext->IASetIndexBuffer(object->indexBuffer, DXGI_FORMAT_R32_UINT, 0);



#pragma region Set the objects texture maps to the shader

	SampleBoolStruct sampleBools;
	if (object->diffuseMap != nullptr)
	{
		this->gDeviceContext->PSSetShaderResources(0, 1, &object->diffuseMap);
		sampleBools.diffuseMap = TRUE;
	}
	else
	{
		sampleBools.diffuseMap = FALSE;
	}

	if (object->normalMap != nullptr)
	{
		this->gDeviceContext->PSSetShaderResources(1, 1, &object->normalMap);
		sampleBools.normalMap = TRUE;
	}
	else
	{
		sampleBools.normalMap = FALSE;
	}

	if (object->specularMap != nullptr)
	{
		this->gDeviceContext->PSSetShaderResources(2, 1, &object->specularMap);
		sampleBools.specularMap = TRUE;
	}
	else
	{
		sampleBools.specularMap = FALSE;
	}

	if (object->glowMap != nullptr)
	{
		this->gDeviceContext->PSSetShaderResources(3, 1, &object->glowMap);
		sampleBools.glowMap = TRUE;
	}
	else
	{
		sampleBools.glowMap = FALSE;
	}

	this->UpdateSampleBoolsBuffer(&sampleBools);
#pragma endregion



	gDeviceContext->GSSetConstantBuffers(CBUFFERPERFRAME_INDEX, 1, &this->cbufferPerFrame);
	gDeviceContext->VSSetConstantBuffers(CBUFFERPERFRAME_INDEX, 1, &this->cbufferPerFrame);
	gDeviceContext->PSSetConstantBuffers(CBUFFERPERFRAME_INDEX, 1, &this->cbufferPerFrame);
	
	//this->gDeviceContext->DrawInstanced(*object->vertexCount, amount, 0, 0);
	this->gDeviceContext->DrawIndexedInstanced((UINT)*object->indexCount, amount, 0, 0, 0);
}

void Renderer::MapLightBufferStructures()
{

	
#pragma region Map point lights
	////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////
	////Map point light structure
	PointLightStruct* pPointLights = this->lightmanager.GetPointLightStruct();
	this->mNumPointLights		   = this->lightmanager.GetNumActivePointLights();

	D3D11_MAPPED_SUBRESOURCE mapRes;
	HRESULT hr = S_OK;
	
	hr = gDeviceContext->Map(lightBuffers[BUFFER_POINTLIGHTS], 0, D3D11_MAP_WRITE_DISCARD, 0, &mapRes);
	if (FAILED(hr))
		MessageBox(NULL, L"Failed to update point lights buffer", L"Error", MB_ICONERROR | MB_OK);

	memcpy(mapRes.pData, (void*)pPointLights, sizeof(PointLightStruct));
	gDeviceContext->Unmap(lightBuffers[BUFFER_POINTLIGHTS], 0);
	this->gDeviceContext->GSSetShaderResources(POINTLIGHTS_BUFFER_INDEX, 1, &pointLightStructuredBuffer);
	this->gDeviceContext->PSSetShaderResources(POINTLIGHTS_BUFFER_INDEX, 1, &pointLightStructuredBuffer);




	////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma region Map SpotLights
	////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////
	////Map Spotlight structure
	//SpotLightStruct* pSpotLights = this->lightmanager.GetSpotLightStruct();
	//this->mNumSpotLights		= this->lightmanager.GetNumActiveSpotLights();

	//D3D11_MAPPED_SUBRESOURCE mapResSpot;
	//hr = S_OK;

	//hr = gDeviceContext->Map(lightBuffers[BUFFER_SPOTLIGHTS], 0, D3D11_MAP_WRITE_DISCARD, 0, &mapResSpot);
	//memcpy(mapResSpot.pData, (void*)pSpotLights, sizeof(SpotLightStruct));
	//gDeviceContext->Unmap(lightBuffers[BUFFER_SPOTLIGHTS], 0);
	//this->gDeviceContext->PSSetShaderResources(SPOTLIGHTS_BUFFER_INDEX, 1, &spotLightStructuredBuffer);
	////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////
#pragma endregion
#pragma region Map DirLights
	////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////
	////Map Dirlight structure
	DirLightStruct* pDirLights		= this->lightmanager.GetDirLightStruct();
	this->mNumDirLights				= this->lightmanager.GetNumActiveDirLights();

	D3D11_MAPPED_SUBRESOURCE mapResDir;
	 hr = S_OK;

	hr = gDeviceContext->Map(lightBuffers[BUFFER_DIRLIGHTS], 0, D3D11_MAP_WRITE_DISCARD, 0, &mapResDir);
	if (FAILED(hr))
		MessageBox(NULL, L"Failed to update directional lights buffer", L"Error", MB_ICONERROR | MB_OK);
	memcpy(mapResDir.pData, (void*)pDirLights, sizeof(DirLightStruct));

	gDeviceContext->Unmap(lightBuffers[BUFFER_DIRLIGHTS], 0);
	this->gDeviceContext->GSSetShaderResources(DIRLIGHTS_BUFFER_INDEX, 1, &dirLightStructuredBuffer);
	this->gDeviceContext->PSSetShaderResources(DIRLIGHTS_BUFFER_INDEX, 1, &dirLightStructuredBuffer);
	////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////
#pragma endregion



}

void Renderer::UpdateCbufferPerFrame()
{

	CbufferPerFrame* tempStruct				= this->sceneCam->GetCameraMatrices();
	tempStruct->mousePos					= this->mouseWorldPos;
	tempStruct->numPointLights				= this->mNumPointLights;
	tempStruct->numSpotLights				= this->mNumSpotLights;
	tempStruct->numDirLights				= this->mNumDirLights;

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

	gDeviceContext->Map(this->cbufferPerFrame, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);


	CbufferPerFrame* tempStructMatrices		= (CbufferPerFrame*)mappedResource.pData;
	*tempStructMatrices						= *tempStruct;
	
	

	gDeviceContext->Unmap(this->cbufferPerFrame, 0);
	
	gDeviceContext->GSSetConstantBuffers(CBUFFERPERFRAME_INDEX, 1, &this->cbufferPerFrame);
	gDeviceContext->PSSetConstantBuffers(CBUFFERPERFRAME_INDEX, 1, &this->cbufferPerFrame);



}

void Renderer::UpdateLightBuffer()
{

	MapLightBufferStructures();

/*
	PointLight* tempLight = this->sceneLightArray;
	
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

	gDeviceContext->Map(this->lightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);


	PointLight* tempLightData = (PointLight*)mappedResource.pData;
	*tempLightData = *tempLight;



	gDeviceContext->Unmap(this->lightBuffer, 0);

	gDeviceContext->GSSetConstantBuffers(LIGHTBUFFER_INDEX, 1, &this->lightBuffer);
	gDeviceContext->PSSetConstantBuffers(LIGHTBUFFER_INDEX, 1, &this->lightBuffer);*/

}

void Renderer::UpdateWorldBuffer(WorldMatrix* worldStruct)
{


	D3D11_MAPPED_SUBRESOURCE mappedResourceWorld;
	ZeroMemory(&mappedResourceWorld, sizeof(mappedResourceWorld));

	//mapping to the matrixbuffer
	this->gDeviceContext->Map(worldBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResourceWorld);

	WorldMatrix* temporaryWorld = (WorldMatrix*)mappedResourceWorld.pData;

	*temporaryWorld = *worldStruct;

	

	this->gDeviceContext->Unmap(worldBuffer, 0);
	gDeviceContext->GSSetConstantBuffers(WORLDBUFFER_INDEX, 1, &this->worldBuffer);
	gDeviceContext->PSSetConstantBuffers(WORLDBUFFER_INDEX, 1, &this->worldBuffer);

}

void Renderer::UpdateSampleBoolsBuffer(SampleBoolStruct * sampleStruct)
{
	D3D11_MAPPED_SUBRESOURCE mappedResourceSampleBool;
	ZeroMemory(&mappedResourceSampleBool, sizeof(mappedResourceSampleBool));

	//mapping to the matrixbuffer
	this->gDeviceContext->Map(sampleBoolsBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResourceSampleBool);

	SampleBoolStruct* temporaryStruct = (SampleBoolStruct*)mappedResourceSampleBool.pData;

	*temporaryStruct = *sampleStruct;



	this->gDeviceContext->Unmap(sampleBoolsBuffer, 0);
	gDeviceContext->PSSetConstantBuffers(SAMPLEBOOLSBUFFER_INDEX, 1, &this->sampleBoolsBuffer);

}

bool Renderer::CreateBuffers()
{


	/* NOTE!!!
	
	The camera and world buffer are set to the geometry shader, the light buffer is set to the pixel shader
	*/
	HRESULT hr;

//-----------------------------------------------------------------------------------------------------------------------------------
		//CbufferPerFrame CONSTANT BUFFER
//-----------------------------------------------------------------------------------------------------------------------------------

	//Creating the cbufferPerFrame constant buffer
	CD3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));

	bufferDesc.ByteWidth			 = sizeof(CbufferPerFrame);
	bufferDesc.BindFlags			 = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.Usage				 = D3D11_USAGE_DYNAMIC;
	bufferDesc.CPUAccessFlags		 = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.MiscFlags			 = 0;
	bufferDesc.StructureByteStride	 = 0;

	hr = this->gDevice->CreateBuffer( &bufferDesc , nullptr , &cbufferPerFrame);
	if (FAILED(hr))
		MessageBox(NULL, L"Failed to create cbufferPerFrame buffer", L"Error", MB_ICONERROR | MB_OK);
	if (SUCCEEDED(hr))
	{

		this->gDeviceContext->GSSetConstantBuffers(CBUFFERPERFRAME_INDEX, 1 , &this->cbufferPerFrame);
		this->gDeviceContext->PSSetConstantBuffers(CBUFFERPERFRAME_INDEX, 1, &this->cbufferPerFrame);
	}

//-----------------------------------------------------------------------------------------------------------------------------------
		//WORLD CONSTANT BUFFER
//-----------------------------------------------------------------------------------------------------------------------------------

 //Creating world constant buffer																 
	CD3D11_BUFFER_DESC bufferDescWorld;
	ZeroMemory(&bufferDescWorld, sizeof(bufferDescWorld));

	bufferDescWorld.ByteWidth				 = sizeof(WorldMatrix);
	bufferDescWorld.BindFlags				 = D3D11_BIND_CONSTANT_BUFFER;
	bufferDescWorld.Usage					 = D3D11_USAGE_DYNAMIC;
	bufferDescWorld.CPUAccessFlags			 = D3D11_CPU_ACCESS_WRITE;
	bufferDescWorld.MiscFlags				 = 0;
	bufferDescWorld.StructureByteStride		 = 0;

	hr = this->gDevice->CreateBuffer( &bufferDescWorld , nullptr , &worldBuffer );

	if (FAILED(hr))
		MessageBox(NULL, L"Failed to create world buffer", L"Error", MB_ICONERROR | MB_OK);
	
	if (SUCCEEDED(hr))
		this->gDeviceContext->GSSetConstantBuffers(WORLDBUFFER_INDEX, 1, &worldBuffer); 


//-----------------------------------------------------------------------------------------------------------------------------------
// Sample Bool buffer (PS)CONSTANT BUFFER
//-----------------------------------------------------------------------------------------------------------------------------------

	//This const buffer holds booleans, so that the gbuffer pass knows what textures the mesh has, so that it wont sample normal map if there is none.

	CD3D11_BUFFER_DESC bufferDescSample;
	ZeroMemory(&bufferDescSample, sizeof(bufferDescSample));

	bufferDescSample.ByteWidth				= sizeof(SampleBoolStruct);
	bufferDescSample.BindFlags				= D3D11_BIND_CONSTANT_BUFFER;
	bufferDescSample.Usage					= D3D11_USAGE_DYNAMIC;
	bufferDescSample.CPUAccessFlags			= D3D11_CPU_ACCESS_WRITE;
	bufferDescSample.MiscFlags				= 0;
	bufferDescSample.StructureByteStride	= 0;

	hr = this->gDevice->CreateBuffer(&bufferDescSample, nullptr, &sampleBoolsBuffer);
	if (FAILED(hr))
		MessageBox(NULL, L"Failed to create sampleBools buffer", L"Error", MB_ICONERROR | MB_OK);
	if (SUCCEEDED(hr))
		this->gDeviceContext->PSSetConstantBuffers(SAMPLEBOOLSBUFFER_INDEX, 1, &sampleBoolsBuffer);

	


	//-----------------------------------------------------------------------------------------------------------------------------------
	//Instanced geometry BUFFER
	//-----------------------------------------------------------------------------------------------------------------------------------

	D3D11_BUFFER_DESC bufferInstancedDesc;
	ZeroMemory(&bufferInstancedDesc, sizeof(bufferInstancedDesc));

	//InstancedObject buffer
	bufferInstancedDesc.BindFlags        = D3D11_BIND_VERTEX_BUFFER;
	bufferInstancedDesc.CPUAccessFlags   = D3D11_CPU_ACCESS_WRITE;
	bufferInstancedDesc.Usage			 = D3D11_USAGE_DYNAMIC;
	bufferInstancedDesc.ByteWidth		 = sizeof(InstancedData) * MAX_INSTANCED_GEOMETRY;

	if (FAILED(hr = gDevice->CreateBuffer(&bufferInstancedDesc, nullptr, &instancedBuffers[INSTANCED_WORLD])))
		MessageBox(NULL, L"Failed to create Instance buffer", L"Renderer Error", MB_ICONERROR | MB_OK);


	//-----------------------------------------------------------------------------------------------------------------------------------
	// LIGHT STRUCTURED BUFFERS (PS)
	//-----------------------------------------------------------------------------------------------------------------------------------





	//////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////
	//POINT LIGHTS
	//////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////
	//Light buffer for structured buffer
	D3D11_BUFFER_DESC lightBufferDesc;
	ZeroMemory(&lightBufferDesc, sizeof(lightBufferDesc));
	lightBufferDesc.BindFlags			= D3D11_BIND_SHADER_RESOURCE;
	lightBufferDesc.Usage				= D3D11_USAGE_DYNAMIC;
	lightBufferDesc.CPUAccessFlags		= D3D11_CPU_ACCESS_WRITE;
	lightBufferDesc.MiscFlags			= D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	lightBufferDesc.ByteWidth			= sizeof(PointLightStruct);
	lightBufferDesc.StructureByteStride = sizeof(PointLight);

	if (FAILED(hr = gDevice->CreateBuffer(&lightBufferDesc, nullptr, &lightBuffers[BUFFER_POINTLIGHTS])))
		MessageBox(NULL, L"Failed to create PointLight buffer", L"Error", MB_ICONERROR | MB_OK);


	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	srvDesc.Format = DXGI_FORMAT_UNKNOWN;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
	srvDesc.Buffer.ElementOffset = 0;
	//srvDesc.Buffer.ElementWidth = sizeof(PointLight);
	srvDesc.Buffer.NumElements = MAX_NUM_POINTLIGHTS;
	if (FAILED(hr = gDevice->CreateShaderResourceView(lightBuffers[BUFFER_POINTLIGHTS], &srvDesc, &pointLightStructuredBuffer)))
		MessageBox(NULL, L"Failed to create PointLight buffer", L"Error", MB_ICONERROR | MB_OK);
	this->gDeviceContext->GSSetShaderResources(POINTLIGHTS_BUFFER_INDEX, 1, &pointLightStructuredBuffer);
	this->gDeviceContext->PSSetShaderResources(POINTLIGHTS_BUFFER_INDEX, 1, &pointLightStructuredBuffer);
	//////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////
	////SPOT LIGHTS
	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////
	//
	////Light buffer for structured buffer
	////D3D11_BUFFER_DESC lightBufferDesc;
	//ZeroMemory(&lightBufferDesc, sizeof(lightBufferDesc));
	//lightBufferDesc.BindFlags			= D3D11_BIND_SHADER_RESOURCE;
	//lightBufferDesc.Usage				= D3D11_USAGE_DYNAMIC;
	//lightBufferDesc.CPUAccessFlags		= D3D11_CPU_ACCESS_WRITE;
	//lightBufferDesc.MiscFlags		    = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	//lightBufferDesc.ByteWidth		    = sizeof(SpotLightStruct);
	//lightBufferDesc.StructureByteStride = sizeof(SpotLight);

	//if (FAILED(hr = gDevice->CreateBuffer(&lightBufferDesc, nullptr, &lightBuffers[BUFFER_SPOTLIGHTS])))
	//	MessageBox(NULL, L"Failed to create SpotLight buffer", L"Error", MB_ICONERROR | MB_OK);

	//if (FAILED(hr = gDevice->CreateShaderResourceView(lightBuffers[BUFFER_SPOTLIGHTS], nullptr, &spotLightStructuredBuffer)))
	//	MessageBox(NULL, L"Failed to create SpotLight buffer", L"Error", MB_ICONERROR | MB_OK);

	//this->gDeviceContext->PSSetShaderResources(SPOTLIGHTS_BUFFER_INDEX, 1, &spotLightStructuredBuffer);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////


	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////
	////DIRECTIONAL LIGHTS
	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////

	//Light buffer for structured buffer
	//D3D11_BUFFER_DESC lightBufferDesc;
	ZeroMemory(&lightBufferDesc, sizeof(lightBufferDesc));
	lightBufferDesc.BindFlags			 = D3D11_BIND_SHADER_RESOURCE;
	lightBufferDesc.Usage				 = D3D11_USAGE_DYNAMIC;
	lightBufferDesc.CPUAccessFlags		 = D3D11_CPU_ACCESS_WRITE;
	lightBufferDesc.MiscFlags			 = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	lightBufferDesc.ByteWidth			 = sizeof(DirLightStruct);
	lightBufferDesc.StructureByteStride  = sizeof(DirectionalLight);

	if (FAILED(hr = gDevice->CreateBuffer(&lightBufferDesc, nullptr, &lightBuffers[BUFFER_DIRLIGHTS])))
		MessageBox(NULL, L"Failed to create DirLight buffer", L"Error", MB_ICONERROR | MB_OK);

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDescDir;
	srvDescDir.Format = DXGI_FORMAT_UNKNOWN;
	srvDescDir.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
	srvDescDir.Buffer.ElementOffset = 0;
	
	srvDescDir.Buffer.NumElements = MAX_NUM_DIRLIGHTS;
	if (FAILED(hr = gDevice->CreateShaderResourceView(lightBuffers[BUFFER_DIRLIGHTS], &srvDescDir, &dirLightStructuredBuffer)))
		MessageBox(NULL, L"Failed to create DirLight buffer", L"Error", MB_ICONERROR | MB_OK);


	this->gDeviceContext->GSSetShaderResources(DIRLIGHTS_BUFFER_INDEX, 1, &dirLightStructuredBuffer);
	this->gDeviceContext->PSSetShaderResources(DIRLIGHTS_BUFFER_INDEX, 1, &dirLightStructuredBuffer);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	return true;
}


