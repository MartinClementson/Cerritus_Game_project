#pragma once
#include "../../Structs/SkeletonStructs.h"
#include "../Headers/BRFImporterStructs.h"
#include "Skeleton\Skeleton.h"
class SkeletonManager
{
private:
	std::vector<Skeleton*> skeletons;
public:
	void AddSkeleton(BRFImporterLib::SkeletonHeader* skelInfo, BRFImporterLib::JointHeader* joints[],
		BRFImporterLib::AnimationHeader* animations[], BRFImporterLib::JointCountHeader* animatedjoints[],
		BRFImporterLib::FrameHeader* frames[]);
	void Initialize();
	void Release();
	SkeletonManager();
	~SkeletonManager();
};

