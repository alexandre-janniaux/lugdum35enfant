#pragma once

#include <vector>
#include <map>
#include <memory>
#include <SFML/System/Time.hpp>

#include "messagebus.hpp"
#include "gamemessage.hpp"
#include "entitypool.hpp"
#include "entitysystem.hpp"
#include "physicbody.hpp"

class CollisionSolver;
//class PhysicBody;

class PhysicInstance : public EntitySystem
{
	public:
		PhysicInstance(CollisionSolver& collisionSolver);

		PhysicBody* bindEntity(Entity entity);
		void unbindEntity(Entity entity);

		void update(sf::Time time, sf::Time step);

	private:
		void onSetEntitySpeedMessage(const SetEntitySpeedMessage& message);
		void onSetEntityPositionMessage(const SetEntityPositionMessage& message);


		CollisionSolver* m_collisionSolver;
		MessageBusProxy<SetEntitySpeedMessage> m_entitySpeedMessage;
		MessageBusProxy<SetEntityPositionMessage> m_entityPositionMessage;
		std::vector<PhysicBody*> m_bodies;
		std::map<Entity, std::unique_ptr<PhysicBody>> m_bodiesOwned;
};
