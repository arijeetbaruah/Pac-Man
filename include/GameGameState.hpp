#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "./BaseState.hpp"

class Player;
class Game;
class Map;

class GameGameState : public BaseState
{
private:
	std::shared_ptr<Player> player;
	std::shared_ptr<Map> map;

public:
	GameGameState(Game* game);

	std::shared_ptr<Map> getMap() const;

	// Inherited via BaseState
	void onEntry() override;
	void handleInput(sf::Event& event) override;
	void onUpdate(sf::Time& elapsed) override;
	void onRender() override;
	void onExit() override;
};

