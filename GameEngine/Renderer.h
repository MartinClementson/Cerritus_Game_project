#pragma once
#include "LibIncluder.h"
#include "Constants.h"
#include "RenderInfo.h"



struct RenderInstructions
{
	XMFLOAT4X4* worldMatrix;
	XMFLOAT4X4* normalWorld;
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;



};
class Renderer
{

private:

public:
	Renderer();
	~Renderer();

	void Initialize(ID3D11DeviceContext* gDeviceContext);
	void Release();
	
	
	void Render(RenderInfoObject* object);
	void Render(RenderInfoUI* object);
	void Render(RenderInfoEnemy* object);
	void Render(RenderInfoChar* object);
	void Render(RenderInfoTrap* object);


};