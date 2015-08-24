#pragma once

struct Entity;

class EntitySystem
{

	protected:
		void registerEntity(const Entity& entity);
		void unregisterEntity(const Entity& entity);
};
