#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class BaseState;
class Game;

class GameGameState;

class GameStateMachine
{
protected:
	Game* game;

	std::shared_ptr<BaseState> currentState;

public:
	std::shared_ptr<GameGameState> gameGameState;

public:
	GameStateMachine(Game* game);

	std::shared_ptr<BaseState> getState() const;

	void handleInput(sf::Event& event);
	void update(sf::Time& elapsed);
	void render();
	void setState(std::shared_ptr<BaseState> state);
};
