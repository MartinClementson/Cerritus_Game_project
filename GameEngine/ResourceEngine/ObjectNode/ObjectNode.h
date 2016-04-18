#pragma once
#include "../../Source/LibIncluder.h"
#include "../../Source/Constants.h"
#include "../../Structs/RenderInfo.h"

class ObjectNode
{
protected:
	ID3D11DeviceContext* gDeviceContext; //a pointer to the device. (not sure if it will be needed her in the end)
	ID3D11Device *gDevice;

	unsigned int objectId = 0;
	unsigned int parentId = 0;


	//custom attr here
public:
	ObjectNode();
	virtual ~ObjectNode();


	virtual void Initialize(ID3D11Device *gDevice, ID3D11DeviceContext* gDeviceContext);
	virtual void Release() {};
	//virtual void Render();
	//virtual void Update();
};

