#pragma once

#include "scene.hpp"
#include "entitysystem.hpp"

#include <map>
#include <memory>

class EntityScene : public EntitySystem, public Scene
{
	public:
		SceneNode* bindEntity(const Entity& entity);
		void unbindEntity(const Entity& entity);

	private:
		std::map<Entity, std::unique_ptr<SceneNode>> m_nodesOwned;
};
