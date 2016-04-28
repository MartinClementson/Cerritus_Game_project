#include "Skeleton.h"

DirectX::XMMATRIX Skeleton::GetParentBindPose(int parentID)
{
	return joints.at(parentID)->bindPose;
}

Skeleton::Skeleton()
{
}

Skeleton::~Skeleton()
{
	for (unsigned int j = 0; j < animations.size(); j++)
	{
		for (unsigned int k = 0; k < animations.at(j)->animatedFrames.size(); k++)
		{
			for (unsigned int l = 0; l < animations.at(j)->animatedFrames.at(k)->frames.size(); l++)
			{
				delete animations.at(j)->animatedFrames.at(k)->frames.at(l);
			}
			delete animations.at(j)->animatedFrames.at(k);
		}
		delete animations.at(j);
	}
}
