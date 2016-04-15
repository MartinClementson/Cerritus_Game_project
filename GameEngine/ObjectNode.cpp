#include "ObjectNode.h"



ObjectNode::ObjectNode()
{
}


ObjectNode::~ObjectNode()
{
}

void ObjectNode::Initialize(ID3D11Device * gDevice, ID3D11DeviceContext * gDeviceContext)
{
	this->gDevice = gDevice;
	this->gDeviceContext = gDeviceContext;

}
