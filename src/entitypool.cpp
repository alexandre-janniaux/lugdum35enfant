#include "entitypool.hpp"
#include "cpp_std_11.hpp"
#include <algorithm>
#include <memory>
#include <assert.h>

bool Entity::operator<(const Entity& other) const
{
	return id < other.id;
}


Entity EntityPool::createEntity()
{
	Entity entity;
	entity.pool = this;
	entity.id = m_currentID++;
	m_systems.push_back(make_unique<std::vector<EntitySystem*>>());
	return entity;
}

EntityPool::~EntityPool()
{
	m_systems.clear();
}

Entity EntityPool::kill(const Entity& entity)
{
	// TODO
}

void EntityPool::registerSystem(EntitySystem* system, const Entity& entity)
{
	assert(entity.pool == this);
	auto& systems = m_systems.at(entity.id);

	auto search = std::find(systems->begin(), systems->end(), system);
	if (search != systems->end())
		systems->push_back(system);
}

void EntityPool::unregisterSystem(EntitySystem* system, const Entity& entity)
{
	assert(entity.pool == this);
	auto& systems = m_systems.at(entity.id);

	auto search = std::find(systems->begin(), systems->end(), system);
	if (search == systems->end())
		systems->erase(search);
}
