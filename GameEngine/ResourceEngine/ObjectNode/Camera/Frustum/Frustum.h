#pragma once
#include "../Constants.h"
#include "../LibIncluder.h"

class Frustum
{
private:
	struct Plane
	{
		DirectX::XMFLOAT3 normal;
		float distance;
	};
	Plane planes[6];
public:
	Frustum();
	~Frustum();

	//INIT
	void CreateFrustum(float FarZ, DirectX::XMFLOAT4X4 projectionMatrix, DirectX::XMFLOAT4X4 &viewMatrix);

	//WIP
	bool CheckCircle(float xCenter, float yCenter, float zCenter, float radius);
	bool CheckCube(float xCenter, float yCenter, float zCenter, float radius);
};