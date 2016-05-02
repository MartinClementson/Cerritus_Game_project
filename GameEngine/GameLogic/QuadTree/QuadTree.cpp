#include "QuadTree.h"


QuadTree::QuadTree(int level, XMFLOAT3 size)
{
	level = level;
	this->size = size;
	nodes.push_back(new QuadTree[4]);
};


QuadTree::QuadTree()
{

}




QuadTree::~QuadTree()
{

}
