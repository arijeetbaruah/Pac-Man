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

    glm::vec2 ghostPos;
    glm::vec2 playerPos;

    for (size_t y = 0; y < map.size(); ++y) {
        std::vector<int> row;
        for (size_t x = 0; x < map[y].length(); ++x) {
            if (map[y][x] == '#') {
                std::shared_ptr<MapNode> mapNode = NULL;
                mapNode = std::make_shared<MapNode>(game, true, glm::vec2(x, y));
                walls.push_back(mapNode);
                game->getEntityManager()->addEntity(mapNode);
                row.push_back(1);
            }
            else if (map[y][x] == 'P') {
                playerPosition = glm::vec2(x * TILE_WIDTH + windowSize.x / 4, y * TILE_HEIGHT);
                playerPos = glm::vec2(x, y);
                row.push_back(0);
            }
            else if (map[y][x] == 'G')
            {
                ghostPos = glm::vec2(x, y);
            }
            else {
                row.push_back(0);
            }
        }
        mapGrid.push_back(row);
    }


    calculatePath(playerPos, ghostPos, [](std::vector<AStarNode*> path) {
        spdlog::info("hi");
    });
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

glm::vec2 Map::getGridFromPosition(const glm::vec2 grid) const
{
    sf::Vector2u windowSize = game->window.getSize();
    return glm::vec2((grid.x - windowSize.x / 4) / TILE_WIDTH, grid.y / TILE_HEIGHT);
}

MapNode::MapNode(Game* aGame, bool aIsWall, glm::vec2 aPosition): BaseEntity(aGame), game(aGame), position(aPosition)
{
    sf::Vector2u windowSize = game->window.getSize();
    setPosition(position.x * TILE_WIDTH + windowSize.x / 4, position.y * TILE_HEIGHT);
    sprite.setSize(sf::Vector2f(TILE_WIDTH, TILE_HEIGHT));

    active = aIsWall;
}

glm::vec2 MapNode::getGridPosition() const
{
    return position;
}

void MapNode::handleInput(sf::Event& event)
{
}

void MapNode::update(sf::Time& elapsed)
{
}

void MapNode::render()
{
    if (active)
    {
        game->window.draw(sprite);
    }
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
    sf::Vector2f position = sprite.getPosition();
    return glm::vec2(position.x, position.y);
}

void MapNode::onCollision(std::shared_ptr<BaseCollider> entity)
{
}

sf::FloatRect MapNode::getBounds()
{
    return sprite.getGlobalBounds();
}
