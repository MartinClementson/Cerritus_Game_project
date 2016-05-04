#pragma once
#include "..\..\..\Source\LibIncluder.h"
#include "..\..\..\Source\Constants.h"

class Gbuffer
{

private:
	ID3D11Device				*gDevice				 = nullptr;
	ID3D11DeviceContext			*gDeviceContext			 = nullptr;

	ID3D11RenderTargetView		*textureRTVs			[TEXTUREAMOUNT] = { nullptr	};
	ID3D11ShaderResourceView	*shaderResourceViews	[TEXTUREAMOUNT] = { nullptr };
	//ID3D11Texture2D				*gBufferTextures		[TEXTUREAMOUNT] = { nullptr };

	ID3D11UnorderedAccessView   *blurUAV				 = nullptr;
	void CreateBlurPassUAV();
public:
	Gbuffer();
	~Gbuffer();

	ID3D11UnorderedAccessView* GetBlurUAV() { return this->blurUAV; }
	ID3D11ShaderResourceView*  GetGlowSRV() { return this->shaderResourceViews[5]; }
	void Initialize(ID3D11Device *gDevice, ID3D11DeviceContext* gDeviceContext);
	void Release();

	void SetToRender(ID3D11DepthStencilView* depthStencilView);		//Set the textures as RTVs so that we can render to them
	void SetToRead(ID3D11RenderTargetView* newTarget);				//Set the textures as Subresources so that we can read/sample from them
	void ClearGbuffer();											//Clear the rendertargetViews
};

