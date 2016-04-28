#pragma once
#include "../Constants.h"
#include "../LibIncluder.h"
struct Skeleton
{
	std::vector<Joint*> joints;
	std::vector<Animation*> animations;
	int skeletonID;
};
struct Joint
{
	DirectX::XMMATRIX bindPose;
	int parentID;
	int jointID;
};
struct Animation
{
	std::vector<AnimationFrames*> animatedFrames;
};
struct AnimationFrames
{
	std::vector<Frames*> frames;
	int jointID;
};
struct Frames
{
	DirectX::XMMATRIX transformation;
};