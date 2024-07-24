#include <SFML/Graphics.hpp>
#include "../include/Game.hpp"

int main()
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

    Game* game = new Game({ desktop.width, desktop.height }, "Pac-Man");
    game->run();
    delete game;
}
