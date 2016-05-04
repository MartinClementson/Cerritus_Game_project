#pragma once
#include "../LibIncluder.h"
#include "../Constants.h"

class ShadowBuffer
{

private:
	ID3D11Device				*gDevice					 = nullptr;
	ID3D11DeviceContext			*gDeviceContext				 = nullptr;

	ID3D11DepthStencilView		*shadowMapStencilView		 = { nullptr };
	ID3D11ShaderResourceView	*shadowShaderResourceView	 = { nullptr };
	ID3D11Texture2D				*shadowMapTexure			 = { nullptr };
public:
	ShadowBuffer();
	~ShadowBuffer();


	void Initialize(ID3D11Device *gDevice, ID3D11DeviceContext* gDeviceContext);
	void Release();

	void ShadowSetToRender();			//Set Shadowmap to render
	void ShadowSetToRead();				//Set shadowmap to be readable
	void ClearShadowGbuffer();			//Clear the shadowmap for the next render
};

