#include "entitysystem.hpp"
#include "entitypool.hpp"

void EntitySystem::registerEntity(const Entity& entity)
{
	entity.pool->registerSystem(this, entity);
}

void EntitySystem::unregisterEntity(const Entity& entity)
{
	entity.pool->unregisterSystem(this, entity);
}
