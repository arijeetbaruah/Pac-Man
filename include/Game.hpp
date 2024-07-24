#pragma once
#include <SFML/Graphics.hpp>
#include <glm/vec2.hpp>
#include <memory>

class GameStateMachine;
class EntityManager;
class Player;
class Map;

class Game
{
public:
	sf::RenderWindow window;

private:
	std::shared_ptr<GameStateMachine> gameStateMachine;
	std::shared_ptr<EntityManager> entityManager;

	bool isFullscreen;

public:
	Game(glm::vec2 aWindowSize, std::string name);

	std::shared_ptr<EntityManager> getEntityManager() const;
	std::shared_ptr<GameStateMachine> getStateMachine() const;

	void run();

private:
	void toggleFullscreen();
};

