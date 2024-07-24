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

	void handleInput(sf::Event& event);
	void update(sf::Time& elapsed);
	void SetState(std::shared_ptr<BaseState> state);
};
