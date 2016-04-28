#pragma once
#include "../../Structs/SkeletonStructs.h"
#include "../Headers/BRFImporterStructs.h"
class SkeletonManager
{
private:
	std::vector<Skeleton*> skeletons;
	DirectX::XMMATRIX GetParentBindPose(int parentID);
public:
	void AddSkeleton();
	void Initialize();
	void Release();
	SkeletonManager();
	~SkeletonManager();
};

