#pragma once
#include "Source\LibIncluder.h"
#include "Source\Constants.h"
class Gbuffer
{

private:
	ID3D11Device				*gDevice = nullptr;
	ID3D11DeviceContext			*gDeviceContext = nullptr;

	ID3D11RenderTargetView		*textureRTVs[5];
	ID3D11ShaderResourceView	*shaderResourceViews[5];
	ID3D11Texture2D				*gBufferTextures[5];
public:
	Gbuffer();
	~Gbuffer();


	void Initialize(ID3D11Device *gDevice, ID3D11DeviceContext* gDeviceContext);
	void Release();
	void SetToRender(); //Set the textures as RTVs so that we can render to them
	void SetToRead();	//Set the textures as Subresources so that we can read/sample from them
};

