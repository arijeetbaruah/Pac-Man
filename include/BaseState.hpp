#pragma once

#include <SFML/Graphics.hpp>
class Game;

class BaseState
{
protected:
	Game* game;
public:
	BaseState(Game* game);

	virtual void onEntry() = 0;
	virtual void handleInput(sf::Event& event) = 0;
	virtual void onUpdate(sf::Time& elapsed) = 0;
	virtual void onExit() = 0;
};

