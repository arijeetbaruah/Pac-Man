#pragma once

#include <vector>
#include <glm/glm.hpp>

class AStarNode;

class AStar
{
public:
	std::vector<AStarNode*> findPath(glm::vec2 startNode, glm::vec2 endNode, const std::vector<std::vector<int>>& grid);

private:
	std::vector<AStarNode*> reconstructPath(AStarNode* endNode) const;
	std::vector<glm::vec2> getNeighbors(AStarNode* node);
	float getDistance(const AStarNode* a, const AStarNode* b) const;

	float heuristic(const glm::vec2& a, const glm::vec2& b);
};

