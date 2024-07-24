#include "../include/Map.hpp"

#include <fstream>
#include <vector>
#include <string>
#include <iostream>

#include "../include/Game.hpp"
#include "../include/EntityManager.hpp"
#include "../include/AStar.hpp"
#include "../include/AStarNode.hpp"

#include <spdlog/spdlog.h>

Map::Map(Game* aGame): game(aGame), mapSize(0,0), playerPosition(0, 0), aStar(std::make_shared<AStar>())
{
}

void Map::load(const std::string& filename)
{
	std::ifstream file(filename);
    std::string line;
    map.clear();

    while (std::getline(file, line)) {
        map.push_back(line);
    }

    sf::Vector2u windowSize = game->window.getSize();

    mapSize.x = map.size();
    mapSize.y = map[0].length();

    for (size_t y = 0; y < map.size(); ++y) {
        std::vector<int> row;
        std::vector<std::shared_ptr<MapNode>> mapNodeRow;
        
        for (size_t x = 0; x < map[y].length(); ++x) {
            std::shared_ptr<MapNode> mapNode = NULL;
            mapNode = std::make_shared<MapNode>(game, false, glm::vec2(x, y));
            mapNodeRow.push_back(mapNode);

            if (map[y][x] == '#') {
                row.push_back(1);
                mapNode->isWall = true;
            }
            else if (map[y][x] == 'P') {
                playerPosition = glm::vec2(x * TILE_WIDTH + windowSize.x / 4, y * TILE_HEIGHT + 50);
                row.push_back(0);
            }
            else if (map[y][x] == 'G')
            {
                row.push_back(0);
            }
            else {
                row.push_back(0);
            }
        }

        walls.push_back(mapNodeRow);
        mapGrid.push_back(row);
    }
}

glm::vec2 Map::getMapSize() const
{
    return mapSize;
}

glm::vec2 Map::getPlayerPosition() const
{
    return playerPosition - glm::vec2(0, 2);
}

void Map::calculatePath(glm::vec2 orgin, glm::vec2 dest, std::function<void(std::vector<AStarNode*>)> callback)
{
    sf::Thread thread(std::bind(&Map::getPaths, this, orgin, dest, callback));
    thread.launch();
}

void Map::getPaths(glm::vec2 origin, glm::vec2 dest, std::function<void(std::vector<AStarNode*>)> callback)
{
    std::vector<AStarNode*> path = aStar->findPath(origin, dest, mapGrid);
    callback(path);
}

std::shared_ptr<AStar> Map::getAStar() const
{
    return aStar;
}

void Map::render()
{
    for (size_t x = 0; x < walls.size(); x++) {
        for (size_t y = 0; y < walls[x].size(); y++) {
            walls[x][y]->render();
        }
    }
}

glm::vec2 Map::getGridFromPosition(const glm::vec2 grid) const
{
    sf::Vector2u windowSize = game->window.getSize();
    return glm::vec2((grid.x - windowSize.x / 4) / TILE_WIDTH, grid.y / TILE_HEIGHT);
}

MapNode::MapNode(Game* aGame, bool aIsWall, glm::vec2 aPosition): game(aGame), gridPosition(aPosition),
    isWall(aIsWall)
{
    sf::Vector2u windowSize = game->window.getSize();

    sprite.setSize(sf::Vector2f(TILE_WIDTH, TILE_HEIGHT));

    setPosition(gridPosition.x * TILE_WIDTH + windowSize.x / 4, gridPosition.y * TILE_HEIGHT + 50);
}

glm::vec2 MapNode::getGridPosition() const
{
    return gridPosition;
}

void MapNode::render()
{
    if (isWall) game->window.draw(sprite);
}

void MapNode::setPosition(const float x, const float y)
{
    sprite.setPosition(x, y);
}

void MapNode::setPosition(const glm::vec2 position)
{
    sprite.setPosition(position.x, position.y);
}

glm::vec2 MapNode::getPosition() const
{
    sf::Vector2f pos = sprite.getPosition();
    return glm::vec2(pos.x, pos.y);
}
