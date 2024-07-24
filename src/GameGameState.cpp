#include "../include/GameGameState.hpp"
#include "../include/EntityManager.hpp"
#include "../include/Player.hpp"
#include "../include/Game.hpp"
#include "../include/Map.hpp"

GameGameState::GameGameState(Game* game) : BaseState(game)
{
    map = std::make_shared<Map>(game);
    map->load("../map/map.txt");

    player = std::make_shared<Player>(game);
    std::shared_ptr<BaseEntity> playerBE = std::dynamic_pointer_cast<BaseEntity>(player);
    game->getEntityManager()->addEntity(std::dynamic_pointer_cast<BaseEntity>(playerBE));
    player->setPosition(map->getPlayerPosition());
}

std::shared_ptr<Map> GameGameState::getMap() const
{
    return map;
}

void GameGameState::onEntry()
{
}

void GameGameState::handleInput(sf::Event& event)
{
}

void GameGameState::onUpdate(sf::Time& elapsed)
{
}

void GameGameState::onExit()
{
}
