#include "Renderer.h"



Renderer::Renderer()
{
	this->resourceManager = new ResourceManager();
}


Renderer::~Renderer()
{
	delete resourceManager;
}

void Renderer::Initialize(ID3D11Device *gDevice, ID3D11DeviceContext* gDeviceContext)
{
	this->gDeviceContext = gDeviceContext;
	resourceManager->Initialize(gDevice, gDeviceContext);
	this->CreateConstantBuffers();
}
void Renderer::Release()
{
	resourceManager->Release();

	SAFE_RELEASE(worldBuffer);
	SAFE_RELEASE(camBuffer);
	SAFE_RELEASE(lightBuffer);

}

#pragma region Overloaded Render functions

void Renderer::Render(RenderInfoObject * object)
{
	RenderInstructions* renderObject;

	//Send the info of the object into the resource manager
	//The resource manager gathers all the rendering info and sends back a renderInstruction
	renderObject = this->resourceManager->GetRenderInfo(object);

	//Render with the given render instruction
	this->Render(renderObject);
}

void Renderer::Render(RenderInfoUI * object)
{

}

void Renderer::Render(RenderInfoEnemy * object)
{
}

void Renderer::Render(RenderInfoChar * object)
{
}

void Renderer::Render(RenderInfoTrap * object)
{
}
void Renderer::RenderPlaceHolder()
{
	RenderInstructions * object;
	object = this->resourceManager->GetPlaceHolderMesh();

	Render(object);

}
#pragma endregion

//Private rendering call
void Renderer::Render(RenderInstructions * object)
{

	
	
#pragma region Check what vertex is to be used

	//We need to make sure that we use the right kind of vertex when rendering
	UINT32 vertexSize;
	
	if (*object->isAnimated == false)
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

	if (object->diffuseMap   != nullptr)
		this->gDeviceContext->PSSetShaderResources(0, 1, &object->diffuseMap);

	if (object->normalMap	 != nullptr)
		this->gDeviceContext->PSSetShaderResources(1, 1, &object->normalMap);
	
	if (object->specularMap	 != nullptr)
		this->gDeviceContext->PSSetShaderResources(2, 1, &object->specularMap);

	if (object->glowMap		 != nullptr)
		this->gDeviceContext->PSSetShaderResources(3, 1, &object->glowMap);

#pragma endregion
	
	
	this->gDeviceContext->DrawIndexed((UINT)*object->indexCount, 0, 0);


}

bool Renderer::CreateConstantBuffers()
{


	/* NOTE!!!
	
	The camera and world buffer are set to the geometry shader, the light buffer is set to the pixel shader
	*/
	HRESULT hr;

//-----------------------------------------------------------------------------------------------------------------------------------
		//CAMERA CONSTANT BUFFER
//-----------------------------------------------------------------------------------------------------------------------------------

	//Creating the Camera constant buffer
	CD3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));

	bufferDesc.ByteWidth			 = sizeof(cameraConstantBuffer);
	bufferDesc.BindFlags			 = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.Usage				 = D3D11_USAGE_DYNAMIC;
	bufferDesc.CPUAccessFlags		 = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.MiscFlags			 = 0;
	bufferDesc.StructureByteStride	 = 0;

	hr = this->gDevice->CreateBuffer( &bufferDesc , nullptr , &camBuffer );

	if (SUCCEEDED(hr))
		this->gDeviceContext->GSSetConstantBuffers( 1 , 1 , &camBuffer ); 


//-----------------------------------------------------------------------------------------------------------------------------------
		//WORLD CONSTANT BUFFER
//-----------------------------------------------------------------------------------------------------------------------------------

 //Creating world constant buffer																 
	CD3D11_BUFFER_DESC bufferDescWorld;
	ZeroMemory(&bufferDescWorld, sizeof(bufferDescWorld));

	bufferDescWorld.ByteWidth				 = sizeof(worldConstantBuffer);
	bufferDescWorld.BindFlags				 = D3D11_BIND_CONSTANT_BUFFER;
	bufferDescWorld.Usage					 = D3D11_USAGE_DYNAMIC;
	bufferDescWorld.CPUAccessFlags			 = D3D11_CPU_ACCESS_WRITE;
	bufferDescWorld.MiscFlags				 = 0;
	bufferDescWorld.StructureByteStride		 = 0;

	hr = this->gDevice->CreateBuffer( &bufferDescWorld , nullptr , &worldBuffer );
	if (SUCCEEDED(hr))
		this->gDeviceContext->GSSetConstantBuffers(0, 1, &worldBuffer); 

//-----------------------------------------------------------------------------------------------------------------------------------
		//LIGHT CONSTANT BUFFER
//-----------------------------------------------------------------------------------------------------------------------------------

	CD3D11_BUFFER_DESC bufferDescLight;
	ZeroMemory(&bufferDescLight, sizeof(bufferDescLight));

	bufferDescLight.ByteWidth				 = sizeof(lightConstantBuffer);
	bufferDescLight.BindFlags				 = D3D11_BIND_CONSTANT_BUFFER;
	bufferDescLight.Usage					 = D3D11_USAGE_DYNAMIC;
	bufferDescLight.CPUAccessFlags			 = D3D11_CPU_ACCESS_WRITE;
	bufferDescLight.MiscFlags				 = 0;
	bufferDescLight.StructureByteStride		 = 0;

	hr = this->gDevice->CreateBuffer(&bufferDescLight, nullptr, &lightBuffer);
	if (SUCCEEDED(hr))
		this->gDeviceContext->PSSetConstantBuffers(	0, 1, &lightBuffer);


	return true;
}


