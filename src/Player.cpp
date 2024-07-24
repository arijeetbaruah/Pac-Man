#include "../include/Player.hpp"
#include "../include/EntityManager.hpp"
#include "../include/Game.hpp"
#include "../include/Map.hpp"
#include "../include/GameGameState.hpp"
#include "../include/GameStateMachine.hpp"
#include <math.h>
#include "../assets/resource.h"
#include "../include/loadTextureFromResource.hpp"
#include <spdlog/spdlog.h>

const float PLAYER_SPEED = 15.0f;

Player::Player(Game* game) : BaseEntity(game), direction(MovementDirection::RIGHT), animationTimer(0), animationIndex(0)
{
	texture = loadTextureFromResource(IDB_PNG1);
	sprite.setTexture(texture);
	initializeAnimation();

	sprite.setTextureRect(animations[direction][animationIndex]);
	sprite.setScale(0.8f, 0.8f);
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

	glm::vec2 dir = getForward();

	glm::vec2 pos = getPosition() + dir * elapsed.asSeconds() * PLAYER_SPEED;

	std::shared_ptr<GameGameState> gameGameState = std::dynamic_pointer_cast<GameGameState>(game->getStateMachine()->getState());
	glm::vec2 gridPos = gameGameState->getMap()->getGridFromPosition(pos);
	spdlog::info("({}, {})", gridPos.x, gridPos.y);

	setPosition(pos);
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
	direction = MovementDirection::RIGHT;
}

void Player::setPosition(const float x, const float y)
{
	sf::Vector2f pos = sprite.getPosition();
	previousPos = glm::vec2(pos.x, pos.y);

	sprite.setPosition(x, y);
}

void Player::setPosition(const glm::vec2 position)
{
	sf::Vector2f pos = sprite.getPosition();
	previousPos = glm::vec2(pos.x, pos.y);

	sprite.setPosition(position.x, position.y);
}

glm::vec2 Player::getPosition() const
{
	sf::Vector2f position = sprite.getPosition();
	return glm::vec2(position.x, position.y);
}

glm::vec2 Player::getForward() const
{
	glm::vec2 dir = glm::vec2(0, 0);
	switch (direction)
	{
	case UP:
		dir = glm::vec2(0, 1);
		break;
	case DOWN:
		dir = glm::vec2(0, -1);
		break;
	case LEFT:
		dir = glm::vec2(-1, 0);
		break;
	case RIGHT:
		dir = glm::vec2(1, 0);
		break;
	}

	return dir;
}
