#include "../include/BaseEntity.hpp"
#include "../include/Game.hpp"

BaseEntity::BaseEntity(Game* aGame) : game(aGame), active(true)
{
}

void BaseEntity::setActive(const bool aActive)
{
	active = aActive;
}

bool BaseEntity::isActive() const
{
	return active;
}
