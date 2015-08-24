#include "entitypool.hpp"
#include <algorithm>
#include <assert.h>

bool Entity::operator<(const Entity& other) const
{
	return id < other.id;
}


Entity EntityPool::createEntity()
{
	Entity entity;
	entity.pool = this;
	entity.id = ++m_currentID;
	return entity;
}

EntityPool::~EntityPool()
{
	for (auto ptr : m_systems)
	{
		if (ptr != nullptr)
			delete ptr;
	}
	m_systems.clear();
}

Entity EntityPool::kill(const Entity& entity)
{
	// TODO
}

void EntityPool::registerSystem(EntitySystem* system, const Entity& entity)
{
	assert(entity.pool == this);
	auto systems = m_systems.at(entity.id);

	auto search = std::find(systems->begin(), systems->end(), system);
	if (search != systems->end())
		systems->push_back(system);
}

void EntityPool::unregisterSystem(EntitySystem* system, const Entity& entity)
{
	assert(entity.pool == this);
	auto systems = m_systems.at(entity.id);

	auto search = std::find(systems->begin(), systems->end(), system);
	if (search == systems->end())
		systems->erase(search);
}
