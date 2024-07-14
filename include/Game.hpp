#pragma once
#include <SFML/Graphics.hpp>
#include <glm/vec2.hpp>

class EntityManager;
class Player;

class Game
{
public:
	sf::RenderWindow window;

private:
	std::shared_ptr<EntityManager> entityManager;
	std::shared_ptr<Player> player;

public:
	Game(glm::vec2 aWindowSize, std::string name);

	std::shared_ptr<EntityManager> getEntityManager() const;

	void run();
};

