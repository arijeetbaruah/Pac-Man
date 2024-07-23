#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class Game;
class BaseEntity;

class EntityManager
{
private:
	Game* game;

	std::vector<std::shared_ptr<BaseEntity>> registry;
public:
	EntityManager(Game* game);

	void addEntity(std::shared_ptr<BaseEntity> entity);
	void clearEntities();

	void handleInput(sf::Event& event);
	void update(sf::Time& elapsed);
	void render();
};
