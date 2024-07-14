#pragma once
#include <SFML/Graphics.hpp>

class BaseCollider
{
public:
	virtual void onCollision(std::shared_ptr<BaseCollider> entity) = 0;
	void calculateCollision(std::shared_ptr<BaseCollider> entity);

	virtual sf::FloatRect getBounds() = 0;
};

