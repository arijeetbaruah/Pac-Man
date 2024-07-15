#include "../include/Map.hpp"
#include "../include/Game.hpp"

#include <fstream>
#include <vector>
#include <string>
#include <iostream>

Map::Map(Game* aGame): game(aGame), mapSize(0,0), playerPosition(0, 0)
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
        for (size_t x = 0; x < map[y].length(); ++x) {
            if (map[y][x] == '#') {
                sf::RectangleShape wallRect;
                wallRect.setPosition(x * TILE_SIZE + windowSize.x / 4, y * TILE_SIZE);
                wallRect.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
                walls.push_back(wallRect);
            }
            else {
                playerPosition = glm::vec2(x * TILE_SIZE + windowSize.x / 4, y * TILE_SIZE);
            }
        }
    }
}

void Map::render()
{
    for (const auto& wall : walls) {
        game->window.draw(wall);
    }
}

glm::vec2 Map::getMapSize() const
{
    return mapSize;
}

glm::vec2 Map::getPlayerPosition() const
{
    return playerPosition;
}
