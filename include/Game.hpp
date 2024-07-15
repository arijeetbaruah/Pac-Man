#pragma once
#include <SFML/Graphics.hpp>
#include <glm/vec2.hpp>

class EntityManager;
class Player;
class Map;

class Game
{
public:
	sf::RenderWindow window;

private:
	std::shared_ptr<EntityManager> entityManager;
	std::shared_ptr<Player> player;
	std::shared_ptr<Map> map;

	bool isFullscreen;

public:
	Game(glm::vec2 aWindowSize, std::string name);

	std::shared_ptr<EntityManager> getEntityManager() const;

	void run();

private:
	void toggleFullscreen();
};

