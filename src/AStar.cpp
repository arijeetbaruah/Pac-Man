#include "../include/AStar.hpp"
#include "../include/AStarNode.hpp"

#include <queue>
#include <unordered_set>
#include <algorithm>

std::vector<AStarNode*> AStar::findPath(AStarNode* startNode, AStarNode* endNode, const std::vector<std::vector<int>>& grid)
{
    std::vector<AStarNode*> openList;
    std::unordered_set<AStarNode*> closedList;

    openList.push_back(startNode);

    while (!openList.empty()) {
        AStarNode* currentNode = *std::min_element(openList.begin(), openList.end(), [](AStarNode* a, AStarNode* b) {
            return a->fCost < b->fCost;
            });

        if (currentNode == endNode) {
            return reconstructPath(endNode);
        }

        openList.erase(std::remove(openList.begin(), openList.end(), currentNode), openList.end());
        closedList.insert(currentNode);

        for (AStarNode* neighbor : getNeighbors(currentNode, grid)) {
            if (closedList.find(neighbor) != closedList.end()) continue;

            float tentativeGCost = currentNode->gCost + getDistance(currentNode, neighbor);

            if (tentativeGCost < neighbor->gCost || std::find(openList.begin(), openList.end(), neighbor) == openList.end()) {
                neighbor->gCost = tentativeGCost;
                neighbor->hCost = neighbor->calculateHCost(endNode);
                neighbor->calculateFCost();
                neighbor->parent = currentNode;

                if (std::find(openList.begin(), openList.end(), neighbor) == openList.end()) {
                    openList.push_back(neighbor);
                }
            }
        }
    }

    return std::vector<AStarNode*>(); // Return empty path if no path is found
}

std::vector<AStarNode*> AStar::reconstructPath(AStarNode* endNode) const
{
    std::vector<AStarNode*> path;
    for (AStarNode* node = endNode; node != nullptr; node = node->parent) {
        path.push_back(node);
    }
    std::reverse(path.begin(), path.end());
    return path;
}

std::vector<AStarNode*> AStar::getNeighbors(AStarNode* node, const std::vector<std::vector<int>>& grid)
{
    std::vector<AStarNode*> neighbors;

    int dx[] = { -1, 1, 0, 0 };
    int dy[] = { 0, 0, -1, 1 };

    for (int i = 0; i < 4; ++i) {
        int newX = node->x + dx[i];
        int newY = node->y + dy[i];

        if (newX >= 0 && newX < grid.size() && newY >= 0 && newY < grid[0].size() && grid[newX][newY] == 0) {
            neighbors.push_back(new AStarNode(newX, newY));
        }
    }

    return neighbors;
}

float AStar::getDistance(const AStarNode* a, const AStarNode* b) const
{
    return std::sqrt(std::pow(a->x - b->x, 2) + std::pow(a->y - b->y, 2));
}
