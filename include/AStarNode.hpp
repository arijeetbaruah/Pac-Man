#pragma once

#include <glm/glm.hpp>

class AStarNode
{
public:
    glm::vec2 pos; // Position of the node
    float gCost, hCost, fCost; // Costs
    AStarNode* parent; // Pointer to the parent node

public:
    AStarNode(glm::vec2 pos, float g, float h, AStarNode* par = NULL);

    float calculateFCost() const;

    bool operator>(const AStarNode* other) const {
        return calculateFCost() > other->calculateFCost();
    }
};

