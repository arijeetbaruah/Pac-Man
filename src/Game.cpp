#include "../include/Game.hpp"
#include "../include/Player.hpp"
#include "../include/EntityManager.hpp"

Game::Game(glm::vec2 aWindowSize, std::string name)
	: window(sf::VideoMode(aWindowSize.x, aWindowSize.y), name)
{
	window.setFramerateLimit(144);

    entityManager = std::make_shared<EntityManager>(this);

    player = std::make_shared<Player>(this);
    std::shared_ptr<BaseEntity> playerBE = std::dynamic_pointer_cast<BaseEntity>(player);
    entityManager->addEntity(std::dynamic_pointer_cast<BaseEntity>(playerBE));
}

std::shared_ptr<EntityManager> Game::getEntityManager() const
{
    return entityManager;
}

void Game::run()
{
    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Time elapsed = clock.restart();
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            entityManager->handleInput(event);
        }

        entityManager->update(elapsed);

        window.clear();
        entityManager->render();
        window.display();
    }
}
