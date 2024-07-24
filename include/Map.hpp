#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <glm/glm.hpp>

#include "./BaseEntity.hpp"
#include "./BaseCollider.hpp"

const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 35;

class Game;
class AStar;
class AStarNode;

class MapNode {
private:
	Game* game;

	sf::RectangleShape sprite;

	glm::vec2 gridPosition;

public:
	bool isWall;

public:
	MapNode(Game* game, bool isWall, glm::vec2 position);

	glm::vec2 getGridPosition() const;

	void render();
	void setPosition(const float x, const float y);
	void setPosition(const glm::vec2 position);
	glm::vec2 getPosition() const;
};

class Map
{
private:
	Game* game;

	std::vector<std::string> map;
	std::vector<std::vector<std::shared_ptr<MapNode>>> walls;
	std::vector<std::vector<int>> mapGrid;

	glm::vec2 mapSize;
	glm::vec2 playerPosition;

	std::shared_ptr<AStar> aStar;


public:
	Map(Game* game);
	void load(const std::string& filename);

	glm::vec2 getMapSize() const;
	glm::vec2 getPlayerPosition() const;

	glm::vec2 getGridFromPosition(const glm::vec2 grid) const;

	void getPaths(glm::vec2 orgin, glm::vec2 dest, std::function<void(std::vector<AStarNode*>)> callback);
	void calculatePath(glm::vec2 orgin, glm::vec2 dest, std::function<void(std::vector<AStarNode*>)> callback);

	std::shared_ptr<AStar> getAStar() const;

	void render();
};

