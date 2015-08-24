#include "entityscene.hpp"
#include "entitypool.hpp"
#include "cpp_std_11.hpp"
#include "scenenode.hpp"

SceneNode& EntityScene::bindEntity(const Entity& entity)
{
	auto search = m_nodesOwned.find(entity);
	if (search != m_nodesOwned.end())
		return *search->second.get();

	registerEntity(entity);
	m_nodesOwned.emplace(entity,make_unique<SceneNode>(getRootNode()));
	return *m_nodesOwned.at(entity);
}

void EntityScene::unbindEntity(const Entity& entity)
{
	auto search = m_nodesOwned.find(entity);
	if (search == m_nodesOwned.end()) return;

	unregisterEntity(entity);
	m_nodesOwned.erase(search);
}
