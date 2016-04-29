#pragma once
#include "../Constants.h"
#include "../LibIncluder.h"
struct Joint
{
	DirectX::XMFLOAT4X4 bindPose;
	int parentID;
	int jointID;
};
struct Frames
{
	DirectX::XMFLOAT4X4 transformation;
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