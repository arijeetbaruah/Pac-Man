#include <SFML/Graphics.hpp>
#include "../include/Game.hpp"

int main()
{
    Game* game = new Game({ 1920u, 1080u }, "Pac-Man");
    game->run();
    delete game;
}
