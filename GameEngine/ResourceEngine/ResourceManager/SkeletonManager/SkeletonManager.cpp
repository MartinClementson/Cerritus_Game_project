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
		for (unsigned int j = 0; j < skeletons.at(i)->animations.size(); j++)
		{
			for (unsigned int k = 0; k < skeletons.at(i)->animations.at(j)->animatedFrames.size(); k++)
			{
				for (unsigned int l = 0; l < skeletons.at(i)->animations.at(j)->animatedFrames.at(k)->frames.size(); l++)
				{
					delete skeletons.at(i)->animations.at(j)->animatedFrames.at(k)->frames.at(l);
				}
				delete skeletons.at(i)->animations.at(j)->animatedFrames.at(k);
			}
			delete skeletons.at(i)->animations.at(j);
		}
		delete skeletons.at(i);
	}
}
