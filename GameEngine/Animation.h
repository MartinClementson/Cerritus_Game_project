#pragma once
class Animation
{
public:
	Animation();
	~Animation();
	void Initialize();
	void Release();
	void Update(double deltaTime);
	void Render();
};

