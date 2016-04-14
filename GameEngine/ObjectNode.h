#pragma once
#include "LibIncluder.h"
#include "Constants.h"

class ObjectNode
{
private:
	ID3D11DeviceContext* gDeviceContext; //a pointer to the device. (not sure if it will be needed her in the end)
	
	unsigned int objectId = 0;
	unsigned int parentId = 0;


	//custom attr here
public:
	ObjectNode();
	virtual ~ObjectNode();


	//virtual void Initialize();
	//virtual void Release();
	//virtual void Render();
	//virtual void Update();
};

