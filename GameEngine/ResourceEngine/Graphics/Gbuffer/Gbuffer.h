#pragma once
#include "Source\LibIncluder.h"
#include "Source\Constants.h"

//////////////////////////////////////////
//DIS IS BECAUSE JOHAN ASKED ME TO CHANGE AMOUNT OF TEXTURES TO MUCH
#define TEXTUREAMOUNT 6
////////////////////////////////////

class Gbuffer
{

private:
	ID3D11Device				*gDevice				 = nullptr;
	ID3D11DeviceContext			*gDeviceContext			 = nullptr;

	ID3D11RenderTargetView		*textureRTVs			[TEXTUREAMOUNT];
	ID3D11ShaderResourceView	*shaderResourceViews	[TEXTUREAMOUNT];
	ID3D11Texture2D				*gBufferTextures		[TEXTUREAMOUNT];
public:
	Gbuffer();
	~Gbuffer();


	void Initialize(ID3D11Device *gDevice, ID3D11DeviceContext* gDeviceContext);
	void Release();
	void SetToRender(); //Set the textures as RTVs so that we can render to them
	void SetToRead();	//Set the textures as Subresources so that we can read/sample from them
};

