#pragma once
#include "./BaseEntity.hpp"
#include "./BaseCollider.hpp"

#include <SFML/Graphics.hpp>
#include <glm/vec2.hpp>

enum MovementDirection {
	UP = 0,
	DOWN,
	LEFT,
	RIGHT
};

class Player : public BaseEntity, public BaseCollider
{
private:
	sf::Sprite sprite;
	sf::Texture texture;

	MovementDirection direction;
	std::map<MovementDirection, std::vector<sf::IntRect>> animations;
	float animationTimer;
	size_t animationIndex;

	glm::vec2 previousPos;
public:
	Player(Game* game);

	// Inherited via BaseEntity
	void handleInput(sf::Event& event) override;
	void update(sf::Time& elapsed) override;
	void render() override;

	void setPosition(const float x, const float y) override;
	void setPosition(const glm::vec2 position) override;
	glm::vec2 getPosition() const override;

	glm::vec2 getForward() const;

	// Inherited via BaseCollider
	void onCollision(std::shared_ptr<BaseCollider> entity) override;
	sf::FloatRect getBounds() override;

private:
	void initializeAnimation();
};
