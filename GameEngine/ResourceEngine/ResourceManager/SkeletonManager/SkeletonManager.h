#pragma once
#include "../../Structs/SkeletonStructs.h"
class SkeletonManager
{
private:
	std::vector<Skeleton*> skeletons;
	DirectX::XMMATRIX GetParentBindPose(int parentID);
public:
	void Initialize();
	void Release();
	SkeletonManager();
	~SkeletonManager();
};

