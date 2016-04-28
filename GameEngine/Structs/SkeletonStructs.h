#pragma once
#include "../Constants.h"
#include "../LibIncluder.h"
struct Joint
{
	DirectX::XMMATRIX bindPose;
	int parentID;
	int jointID;
};
struct Frames
{
	DirectX::XMMATRIX transformation;
};
struct AnimationFrames
{
	std::vector<Frames*> frames;
	int jointID;
};
struct Animation
{
	std::vector<AnimationFrames*> animatedFrames;
};