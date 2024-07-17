#pragma once

#include <vector>

class AStarNode;

class AStar
{
public:
	std::vector<AStarNode*> findPath(AStarNode* startNode, AStarNode* endNode, const std::vector<std::vector<int>>& grid);

private:
	std::vector<AStarNode*> reconstructPath(AStarNode* endNode) const;
	std::vector<AStarNode*> getNeighbors(AStarNode* node, const std::vector<std::vector<int>>& grid);
	float getDistance(const AStarNode* a, const AStarNode* b) const;
};

