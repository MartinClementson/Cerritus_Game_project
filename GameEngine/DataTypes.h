#pragma once


struct Float3
{
	float x;
	float y;
	float z;

	Float3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Float3() {};
};

struct Double3
{
	double x;
	double y;
	double z;

	Double3() {};

	Double3(double x, double y, double z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
};




struct Vertex
{
	float x,y,z;

	Vertex(Float3 pos)
	{
		x = pos.x;
		y = pos.y;
		z = pos.z;
	}
	Vertex() {};

};

//struct Vertex
//{
//	Float3 Position;
//
//	Vertex(Float3 pos)
//	{
//		Position = pos;
//	}
//	Vertex() {};
//
//};

struct AnimVert
{

};