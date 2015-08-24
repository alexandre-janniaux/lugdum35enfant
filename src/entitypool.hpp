#pragma once

#include <vector>

class EntityPool;
class EntitySystem;

struct Entity
{
	using ID = unsigned long long;

	ID id;
	EntityPool* pool;

	bool operator<(const Entity& other) const;
};

class EntityPool
{
	public:
		~EntityPool();

		Entity createEntity();
		Entity kill(const Entity& entity);

	private:
		friend class EntitySystem;
		void registerSystem(EntitySystem* system, const Entity& entity);
		void unregisterSystem(EntitySystem* system, const Entity& entity);

		std::vector<std::vector<EntitySystem*>*> m_systems;
		Entity::ID m_currentID = 1;


};
