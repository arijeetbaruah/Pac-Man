#pragma once
#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>

class Game;

class BaseEntity
{
protected:
	Game* game;
	bool active;

public:
	BaseEntity(Game* aGame);

	void setActive(const bool aActive);
	bool isActive() const;

	virtual void handleInput(sf::Event& event) = 0;
	virtual void update(sf::Time& elapsed) = 0;
	virtual void render() = 0;

	virtual void setPosition(const float x, const float y) = 0;
	virtual void setPosition(const glm::vec2 position) = 0;
	virtual glm::vec2 getPosition() const = 0;
};

