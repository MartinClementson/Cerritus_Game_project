#include "Renderer.h"



Renderer::Renderer()
{
	this->resourceManager = new ResourceManager();
}


Renderer::~Renderer()
{
	delete resourceManager;
}

void Renderer::Initialize(ID3D11DeviceContext * gDeviceContext)
{
	this->gDeviceContext = gDeviceContext;
	resourceManager->Initialize();
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

	//Render using the given render instruction
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
#pragma endregion

//Private rendering call
void Renderer::Render(RenderInstructions * object)
{

	float clearColor[] = { 0, 0, 0, 1 };

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
	this->gDeviceContext->IASetVertexBuffers(0, 1, &object->vertexBuffer, &vertexSize, &offset);
	this->gDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	this->gDeviceContext->IASetIndexBuffer(object->indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	


#pragma region Set the objects texture maps to the shader

	if (object->diffuse  != nullptr)
		this->gDeviceContext->PSSetShaderResources(0, 1, &object->diffuse);

	if (object->normal	 != nullptr)
		this->gDeviceContext->PSSetShaderResources(1, 1, &object->normal);
	
	if (object->specular != nullptr)
		this->gDeviceContext->PSSetShaderResources(2, 1, &object->specular);

	if (object->glow	 != nullptr)
		this->gDeviceContext->PSSetShaderResources(3, 1, &object->glow);

#pragma endregion
	
	this->gDeviceContext->DrawIndexed((UINT)object->indexCount, 0, 0);
	

}


