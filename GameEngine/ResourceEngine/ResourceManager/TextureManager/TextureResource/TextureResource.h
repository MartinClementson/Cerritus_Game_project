#pragma once
#include "../../../../Structs/RenderInfo.h"
#include "../../../../Source/Constants.h"
#include "../../../../Source/LibIncluder.h"
#include "../../../../Enumerations/Enumerations.h"

class TextureResource
{
private:
	ID3D11DeviceContext* gDeviceContext = nullptr;
	ID3D11ShaderResourceView* texSRV = nullptr;

	bool isActive = false;
	TextureType type;

	unsigned int textureID;
public:
	TextureResource();
	~TextureResource();

	void Initialize();
	virtual void Release();
	void Render();
	void Update();
	void SetAsActive();
	void SetAsInactive();
	bool GetIsActive();
};