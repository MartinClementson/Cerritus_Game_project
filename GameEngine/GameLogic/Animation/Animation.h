#pragma once
class Animation
{
public:
	Animation();
	virtual ~Animation();
	void Initialize();
	void Release();
	void Update();
	void Render();
};

