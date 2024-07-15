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

void Player::setPosition(const float x, const float y)
{
	circle.setPosition(x, y);
}

void Player::setPosition(const glm::vec2 position)
{
	circle.setPosition(position.x, position.y);
}

glm::vec2 Player::getPosition() const
{
	sf::Vector2f position = circle.getPosition();
	return glm::vec2(position.x, position.y);
}
