#pragma once
#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>

const int TILE_SIZE = 32;

class Game;

class Map
{
private:
	Game* game;

	std::vector<std::string> map;
	std::vector<sf::RectangleShape> walls;

	glm::vec2 mapSize;
	glm::vec2 playerPosition;

public:
	Map(Game* game);
	void load(const std::string& filename);

	void render();

	glm::vec2 getMapSize() const;
	glm::vec2 getPlayerPosition() const;
};

