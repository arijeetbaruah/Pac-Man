#include "../include/Player.hpp"
#include "../include/EntityManager.hpp"
#include "../include/Game.hpp"
#include "../include/Map.hpp"
#include <Windows.h>
#include <math.h>
#include "../assets/resource.h"
#include "../include/loadTextureFromResource.hpp"
#include <spdlog/spdlog.h>

Player::Player(Game* game) : BaseEntity(game), direction(MovementDirection::RIGHT), animationTimer(0), animationIndex(0)
{
	texture = loadTextureFromResource(IDB_PNG1);
	sprite.setTexture(texture);
	initializeAnimation();

	sprite.setTextureRect(animations[direction][animationIndex]);
	sprite.setScale(0.9f, 0.9f);
}

void Player::handleInput(sf::Event& event)
{
}

void Player::update(sf::Time& elapsed)
{
	animationTimer += elapsed.asSeconds();
	if (animationTimer >= 0.5f) {
		animationIndex++;
		animationIndex = animations[direction].size() == animationIndex ? 0 : animationIndex;
		sprite.setTextureRect(animations[direction][animationIndex]);
		animationTimer = 0;
	}
}

void Player::render()
{
	game->window.draw(sprite);
}

void Player::onCollision(std::shared_ptr<BaseCollider> entity)
{
	
}

sf::FloatRect Player::getBounds()
{
	return sprite.getGlobalBounds();
}

void Player::initializeAnimation()
{
	std::vector<sf::IntRect> rightMovementAnimation;

	rightMovementAnimation.push_back(sf::IntRect(50 * 17, 0, 50, 50));
	rightMovementAnimation.push_back(sf::IntRect(50 * 17, 50, 50, 50));
	rightMovementAnimation.push_back(sf::IntRect(50 * 17, 100, 50, 50));
	rightMovementAnimation.push_back(sf::IntRect(50 * 17, 50, 50, 50));

	animations[MovementDirection::RIGHT] = rightMovementAnimation;
}

void Player::setPosition(const float x, const float y)
{
	sprite.setPosition(x, y);
}

void Player::setPosition(const glm::vec2 position)
{
	sprite.setPosition(position.x, position.y);
}

glm::vec2 Player::getPosition() const
{
	sf::Vector2f position = sprite.getPosition();
	return glm::vec2(position.x, position.y);
}
