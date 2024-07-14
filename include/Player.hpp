#pragma once
#include "./BaseEntity.hpp"
#include "./BaseCollider.hpp"

#include <SFML/Graphics.hpp>
#include <glm/vec2.hpp>

class Player : public BaseEntity, public BaseCollider
{
private:
	sf::CircleShape circle;

public:
	Player(Game* game);

	// Inherited via BaseEntity
	void handleInput(sf::Event& event) override;
	void update(sf::Time& elapsed) override;
	void render() override;

	// Inherited via BaseCollider
	void onCollision(std::shared_ptr<BaseCollider> entity) override;
	sf::FloatRect getBounds() override;
};
