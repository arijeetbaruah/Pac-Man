#include "../include/EntityManager.hpp"
#include "../include/Game.hpp"
#include "../include/BaseEntity.hpp"
#include "../include/BaseCollider.hpp"

EntityManager::EntityManager(Game* aGame): game(aGame)
{
}

void EntityManager::addEntity(std::shared_ptr<BaseEntity> entity)
{
	registry.push_back(entity);
}

void EntityManager::clearEntities()
{
	registry.clear();
}

void EntityManager::handleInput(sf::Event& event)
{
	for (size_t i = 0; i < registry.size(); i++)
	{
		registry[i]->handleInput(event);
	}
}

void EntityManager::update(sf::Time& elapsed)
{
	std::vector<std::shared_ptr<BaseEntity>> colliders;
	std::copy_if(registry.begin(), registry.end(), std::back_inserter(colliders), [](std::shared_ptr<BaseEntity> entity) {
		return std::dynamic_pointer_cast<BaseCollider>(entity) != NULL;
	});

	// Check Collision
	for (size_t i = 0; i < colliders.size(); i++)
	{
		if (colliders[i]->isActive())
		{
			for (size_t j = 0; j < colliders.size(); j++)
			{
				if (colliders[i]->isActive() && colliders[j]->isActive())
				{
					std::shared_ptr<BaseCollider> cb1 = std::dynamic_pointer_cast<BaseCollider>(colliders[i]);
					std::shared_ptr<BaseCollider> cb2 = std::dynamic_pointer_cast<BaseCollider>(colliders[j]);
					cb1->calculateCollision(cb2);
				}
			}
		}
	}

	for (size_t i = 0; i < registry.size(); i++)
	{
		registry[i]->update(elapsed);
	}
}

void EntityManager::render()
{
	for (size_t i = 0; i < registry.size(); i++)
	{
		registry[i]->render();
	}
}
