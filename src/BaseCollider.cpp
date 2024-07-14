#include "../include/BaseCollider.hpp"

void BaseCollider::calculateCollision(std::shared_ptr<BaseCollider> entity)
{
	if (getBounds().intersects(entity->getBounds()))
	{
		onCollision(entity);
	}
}
