#include "SkeletonManager.h"



DirectX::XMMATRIX SkeletonManager::GetParentBindPose(int parentID)
{
	return DirectX::XMMATRIX();
}

void SkeletonManager::AddSkeleton(BRFImporterLib::SkeletonHeader* skelInfo, BRFImporterLib::JointHeader* joints[])
{
}

void SkeletonManager::Initialize()
{
}

void SkeletonManager::Release()
{
}

SkeletonManager::SkeletonManager()
{
}


SkeletonManager::~SkeletonManager()
{
	for (unsigned int i = 0; i < skeletons.size(); i++)
	{
		
	}
}
