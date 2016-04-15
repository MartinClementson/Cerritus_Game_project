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
	resourceManager->Initialize(gDevice,gDeviceContext);
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
void Renderer::Render()
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
	//this->gDeviceContext->Draw(*object->vertexCount, 0);

}


