#pragma once

#include <functional>
#include <vector>
#include "physicparticle.hpp"

class PhysicBody;

class CollisionSolver
{
	public:
		CollisionSolver(std::function<void(PhysicBody&, PhysicBody&)> callback_collision);

		void checkCollision(const std::vector<PhysicBody*>& bodies, const std::vector<PhysicParticle>& newParticules);

	private:
		std::function<void(PhysicBody&, PhysicBody&)> m_callbackCollision;
};
