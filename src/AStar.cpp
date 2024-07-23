#include "../include/AStar.hpp"

#include <queue>
#include <unordered_set>
#include <algorithm>
#include <SFML/System/Vector2.hpp>
#include <unordered_map>

#include "../include/AStarNode.hpp"

std::vector<AStarNode*> AStar::findPath(glm::vec2 start, glm::vec2 end, const std::vector<std::vector<int>>& grid)
{
    std::priority_queue<AStarNode*, std::vector<AStarNode*>, std::greater<AStarNode*>> openSet;
    std::unordered_map<int, AStarNode*> allNodes;

    auto hashNode = [](const glm::vec2& pos) { return pos.y * 10000 + pos.x; };

    AStarNode* startNode= new AStarNode(start, 0.0f, heuristic(start, end));
    openSet.push(startNode);
    allNodes[hashNode(start)] = startNode;

    while (!openSet.empty()) {
        AStarNode* currentNode = openSet.top();
        openSet.pop();

        if (currentNode->pos == end) {
            return reconstructPath(allNodes[hashNode(currentNode->pos)]);
        }

        for (const auto& neighborPos : getNeighbors(currentNode)) {
            if (neighborPos.x < 0 || neighborPos.x >= grid[0].size() ||
                neighborPos.y < 0 || neighborPos.y >= grid.size() ||
                grid[neighborPos.y][neighborPos.x] == 1) {
                continue;
            }

            float tentativeGCost = currentNode->gCost + 1.0f;
            int neighborHash = hashNode(neighborPos);

            if (allNodes.find(neighborHash) == allNodes.end() || tentativeGCost < allNodes[neighborHash]->gCost) {
                AStarNode* neighborNode = new AStarNode(neighborPos, tentativeGCost, heuristic(neighborPos, end), allNodes[hashNode(currentNode->pos)]);
                allNodes[neighborHash] = neighborNode;
                openSet.push(neighborNode);
            }
        }
    }

    return std::vector<AStarNode*>(); // Return empty path if no path is found
}

std::vector<AStarNode*> AStar::reconstructPath(AStarNode* endNode) const
{
    std::vector<AStarNode*> path;
    AStarNode* current = endNode;
    while (current) {
        path.push_back(current);
        current = current->parent;
    }
    std::reverse(path.begin(), path.end());
    return path;
}

std::vector<glm::vec2> AStar::getNeighbors(AStarNode* node)
{
    std::vector<glm::vec2> neighbors;

    neighbors.push_back({ node->pos.x - 1, node->pos.y });
    neighbors.push_back({ node->pos.x + 1, node->pos.y });
    neighbors.push_back({ node->pos.x, node->pos.y - 1 });
    neighbors.push_back({ node->pos.x, node->pos.y + 1 });

    return neighbors;
}

float AStar::getDistance(const AStarNode* a, const AStarNode* b) const
{
    return std::sqrt(std::pow(a->pos.x - b->pos.x, 2) + std::pow(a->pos.y - b->pos.y, 2));
}

float AStar::heuristic(const glm::vec2& a, const glm::vec2& b)
{
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}
