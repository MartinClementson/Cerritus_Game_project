#include "SkeletonManager.h"



DirectX::XMMATRIX SkeletonManager::GetParentBindPose(int parentID)
{
	return DirectX::XMMATRIX();
}

void SkeletonManager::AddSkeleton()
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
