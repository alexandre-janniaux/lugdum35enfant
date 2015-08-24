#pragma once

#include <vector>
#include <memory>

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
		using SystemCollectionPtr = std::unique_ptr<std::vector<EntitySystem*>>;
		friend class EntitySystem;
		void registerSystem(EntitySystem* system, const Entity& entity);
		void unregisterSystem(EntitySystem* system, const Entity& entity);

		std::vector<SystemCollectionPtr> m_systems;
		Entity::ID m_currentID = 0;


};
