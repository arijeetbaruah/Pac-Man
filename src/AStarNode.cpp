#include "../include/AStarNode.hpp"

#include <vector>
#include <cmath>

AStarNode::AStarNode(glm::vec2 pos, float g, float h, AStarNode* par) : pos(pos), gCost(g), hCost(h), parent(par)
{
}

float AStarNode::calculateFCost() const
{
	return gCost + hCost;
}
