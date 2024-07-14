#include "../include/Player.hpp"
#include "../include/EntityManager.hpp"
#include "../include/Game.hpp"

Player::Player(Game* game) : BaseEntity(game)
{
	circle = sf::CircleShape(10);
	circle.setPosition(10, 10);
}

void Player::handleInput(sf::Event& event)
{
}

void Player::update(sf::Time& elapsed)
{
}

void Player::render()
{
	game->window.draw(circle);
}

void Player::onCollision(std::shared_ptr<BaseCollider> entity)
{
}

sf::FloatRect Player::getBounds()
{
	return circle.getGlobalBounds();
}
