#pragma

#include <vector>

class EntityPool;
class EntitySystem;

struct Entity
{
	using ID = unsigned long long;

	ID id;
	EntityPool* pool;
};

class EntityPool
{
	public:
		~EntityPool();

		Entity createEntity();
		Entity kill(const Entity& entity);

	private:
		std::vector<std::vector<EntitySystem*>*> m_systems;
		Entity::ID m_currentID = 1;


};
