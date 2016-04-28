#pragma once
#include "../../../../Structs/SkeletonStructs.h"
class Skeleton
{
private:
	int skeletonID;
public:
	DirectX::XMMATRIX GetParentBindPose(int parentID);
	std::vector<Joint*> joints;
	std::vector<Animation*> animations;
	Skeleton();
	~Skeleton();
};

