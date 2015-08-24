#include "entitypool.hpp"

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
