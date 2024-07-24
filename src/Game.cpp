#include "../include/Game.hpp"
#include "../include/Player.hpp"
#include "../include/EntityManager.hpp"
#include "../include/GameStateMachine.hpp"

Game::Game(glm::vec2 aWindowSize, std::string name)
	: window(sf::VideoMode(aWindowSize.x, aWindowSize.y), name, sf::Style::Fullscreen),
    isFullscreen(true)
{
	window.setFramerateLimit(144);

    entityManager = std::make_shared<EntityManager>(this);
    gameStateMachine = std::make_shared<GameStateMachine>(this);
}

std::shared_ptr<EntityManager> Game::getEntityManager() const
{
    return entityManager;
}

std::shared_ptr<GameStateMachine> Game::getStateMachine() const
{
    return gameStateMachine;
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
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Enter && event.key.alt)
                {
                    toggleFullscreen();
                }
            }
            entityManager->handleInput(event);
            gameStateMachine->handleInput(event);
        }

        entityManager->update(elapsed);
        gameStateMachine->update(elapsed);

        window.clear();
        gameStateMachine->render();
        entityManager->render();
        window.display();
    }
}

void Game::toggleFullscreen()
{
    // Get the current desktop resolution
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

    // Save the current view to restore later
    sf::View currentView = window.getView();

    if (isFullscreen) {
        window.create(sf::VideoMode(800, 600), "Pac-Man", sf::Style::Default);
        isFullscreen = false;
    }
    else {
        window.create(desktop, "Pac-Man", sf::Style::Fullscreen);
        isFullscreen = true;
    }

    // Restore the view to the new window
    window.setView(currentView);
}
