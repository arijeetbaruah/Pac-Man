#include "../include/AStarNode.hpp"

#include <vector>
#include <cmath>

AStarNode::AStarNode(int x, int y) : x(x), y(y), gCost(0), hCost(0), fCost(0), parent(nullptr)
{
}

void AStarNode::calculateFCost()
{
	fCost = gCost + hCost;
}

float AStarNode::calculateHCost(const AStarNode* endNode) const
{
	return std::sqrt(std::pow(x - endNode->x, 2) + std::pow(y - endNode->y, 2));;
}
