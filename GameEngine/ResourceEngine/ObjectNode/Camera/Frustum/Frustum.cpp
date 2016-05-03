#include "../Frustum/Frustum.h"

Frustum::Frustum()
{
	for (int i = 0; i < 6; i++)
	{
		planes[i].normal.x = 0.0f;
		planes[i].normal.y = 0.0f;
		planes[i].normal.z = 0.0f;
		planes[i].distance = 0.0f;
	}
}

Frustum::~Frustum()
{
}



void Frustum::CreateFrustum(float FarZ, DirectX::XMFLOAT4X4 projectionMatrix, DirectX::XMFLOAT4X4 &viewMatrix)
{
	float zMin = -projectionMatrix._43 / projectionMatrix._33;
	float r = (FarZ / (FarZ - zMin));
	projectionMatrix._33 = r;
	projectionMatrix._43 = -r * zMin;

	DirectX::XMMATRIX temp = DirectX::XMMatrixMultiply(DirectX::XMLoadFloat4x4(&viewMatrix), DirectX::XMLoadFloat4x4(&projectionMatrix));
	DirectX::XMMatrixTranspose(temp);
	DirectX::XMFLOAT4X4 m;
	DirectX::XMStoreFloat4x4(&m, temp);

	//PLANE CALC
	//left
	this->planes[0].normal.x = (m._14 + m._11);
	this->planes[0].normal.y = (m._24 + m._21);
	this->planes[0].normal.z = (m._34 + m._31);
	this->planes[0].distance = (m._44 + m._41);
	//right
	this->planes[1].normal.x = (m._14 - m._11);
	this->planes[1].normal.y = (m._24 - m._21);
	this->planes[1].normal.z = (m._34 - m._31);
	this->planes[1].distance = (m._44 - m._41);
	//top
	this->planes[2].normal.x = (m._14 - m._12);
	this->planes[2].normal.y = (m._24 - m._22);
	this->planes[2].normal.z = (m._34 - m._32);
	this->planes[2].distance = (m._44 - m._42);
	//bottom
	this->planes[3].normal.x = (m._14 + m._12);
	this->planes[3].normal.y = (m._24 + m._22);
	this->planes[3].normal.z = (m._34 + m._32);
	this->planes[3].distance = (m._44 + m._42);
	//near
	this->planes[4].normal.x = (m._14 + m._13);
	this->planes[4].normal.y = (m._24 + m._23);
	this->planes[4].normal.z = (m._34 + m._33);
	this->planes[4].distance = (m._44 + m._43);
	//far
	this->planes[5].normal.x = (m._14 - m._13);
	this->planes[5].normal.y = (m._24 - m._23);
	this->planes[5].normal.z = (m._34 - m._33);
	this->planes[5].distance = (m._44 - m._43);

	for (unsigned int i = 0; i < 6; i++)
	{
		float lengthSquared =
			planes[i].normal.x * planes[i].normal.x +
			planes[i].normal.y * planes[i].normal.y +
			planes[i].normal.z * planes[i].normal.z;

		float denom = 1.0f / sqrt(lengthSquared);

		planes[i].normal.x *= denom;
		planes[i].normal.y *= denom;
		planes[i].normal.z *= denom;
		planes[i].distance *= denom;
	}
}

bool Frustum::CheckCircle(float xCenter, float yCenter, float zCenter, float radius)
{
	DirectX::XMFLOAT3 centerPoint = { xCenter , yCenter , zCenter };

	for (unsigned int i = 0; i < 6; i++)
	{
		DirectX::XMFLOAT4 plane =
		{
			planes[i].normal.x,
			planes[i].normal.y,
			planes[i].normal.z,
			planes[i].distance
		};
		if (DirectX::XMPlaneDotCoord(DirectX::XMLoadFloat4(&plane), DirectX::XMLoadFloat3(&centerPoint)).m128_f32[0] < -radius)
		{
			return false;
		}
		return true;
	}
}

//feed me positions!
bool Frustum::CheckCube(float xCenter, float yCenter, float zCenter, float radius)
{
	for (unsigned int i = 0; i < 6; i++)
	{
		DirectX::XMFLOAT4 plane =
		{
			this->planes[i].normal.x,
			this->planes[i].normal.y,
			this->planes[i].normal.z,
			this->planes[i].distance
		};

		DirectX::XMFLOAT3 point;
		point = { (xCenter - radius), (yCenter - radius), (zCenter - radius) };
		if (DirectX::XMPlaneDotCoord(XMLoadFloat4(&plane), DirectX::XMLoadFloat3(&point)).m128_f32[0] >= 0.0f)
			continue;

		point = { (xCenter + radius), (yCenter - radius), (zCenter - radius) };
		if (DirectX::XMPlaneDotCoord(XMLoadFloat4(&plane), DirectX::XMLoadFloat3(&point)).m128_f32[0] >= 0.0f)
			continue;

		point = { (xCenter - radius), (yCenter + radius), (zCenter - radius) };
		if (DirectX::XMPlaneDotCoord(XMLoadFloat4(&plane), DirectX::XMLoadFloat3(&point)).m128_f32[0] >= 0.0f)
			continue;

		point = { (xCenter + radius), (yCenter + radius), (zCenter - radius) };
		if (DirectX::XMPlaneDotCoord(XMLoadFloat4(&plane), DirectX::XMLoadFloat3(&point)).m128_f32[0] >= 0.0f)
			continue;

		point = { (xCenter - radius), (yCenter - radius), (zCenter + radius) };
		if (DirectX::XMPlaneDotCoord(XMLoadFloat4(&plane), DirectX::XMLoadFloat3(&point)).m128_f32[0] >= 0.0f)
			continue;

		point = { (xCenter + radius), (yCenter - radius), (zCenter + radius) };
		if (DirectX::XMPlaneDotCoord(XMLoadFloat4(&plane), DirectX::XMLoadFloat3(&point)).m128_f32[0] >= 0.0f)
			continue;

		point = { (xCenter - radius), (yCenter + radius), (zCenter + radius) };
		if (DirectX::XMPlaneDotCoord(XMLoadFloat4(&plane), DirectX::XMLoadFloat3(&point)).m128_f32[0] >= 0.0f)
			continue;

		point = { (xCenter + radius), (yCenter + radius), (zCenter + radius) };
		if (DirectX::XMPlaneDotCoord(XMLoadFloat4(&plane), DirectX::XMLoadFloat3(&point)).m128_f32[0] >= 0.0f)
			continue;

		return false;
	}

	return true;
}
