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
	ID3D11Texture2D				*gBufferTextures		[TEXTUREAMOUNT] = { nullptr };

	ID3D11DepthStencilView		*gBufferShadowMapStencilViews		[SHADOWMAPAMOUNT] = { nullptr };
	ID3D11ShaderResourceView	*shadowShaderResourceViews			[SHADOWMAPAMOUNT] = { nullptr };
	ID3D11Texture2D				*gBufferShadowMapTexures			[SHADOWMAPAMOUNT] = { nullptr };
public:
	Gbuffer();
	~Gbuffer();


	void Initialize(ID3D11Device *gDevice, ID3D11DeviceContext* gDeviceContext);
	void Release();
	void SetToRender(ID3D11DepthStencilView* depthStencilView);																					//Set the textures as RTVs so that we can render to them
	void SetToRead(ID3D11RenderTargetView* newTarget);		//Set the textures as Subresources so that we can read/sample from them
	void ShadowSetToRead();
	void ClearShadowGbuffer();
	void ClearGbuffer();																				//Clear the rendertargetViews
	void ShadowSetToRender();
};

