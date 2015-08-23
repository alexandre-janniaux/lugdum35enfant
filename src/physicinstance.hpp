#pragma once

#include <vector>
#include <memory>
#include <SFML/System/Time.hpp>

class CollisionSolver;
class PhysicBody;

class PhysicInstance
{
	public:
		PhysicInstance(CollisionSolver& collisionSolver);


		void update(sf::Time time, sf::Time step);

	private:
		CollisionSolver* m_collisionSolver;
		std::vector<PhysicBody*> m_bodies;

};
