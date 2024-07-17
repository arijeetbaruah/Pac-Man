#pragma once

class AStarNode
{
public:
    int x, y; // Position of the node
    float gCost, hCost, fCost; // Costs
    AStarNode* parent; // Pointer to the parent node

public:
    AStarNode(int x, int y);

    void calculateFCost();
    float calculateHCost(const AStarNode* endNode) const;
};

