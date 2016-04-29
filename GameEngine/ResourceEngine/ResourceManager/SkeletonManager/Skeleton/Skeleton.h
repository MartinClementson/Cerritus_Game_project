#pragma once
#include "../../../../Structs/SkeletonStructs.h"
class Skeleton
{
private:
	int skeletonID;
	std::vector<Joint*> joints;
	std::vector<Animation*> animations;
public:
	DirectX::XMMATRIX GetParentBindPose(int parentID);
	Skeleton();
	~Skeleton();
};

