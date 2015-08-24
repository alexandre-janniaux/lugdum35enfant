#pragma once

#include <functional>
#include <vector>
#include "physicparticle.hpp"

class PhysicBody;

class CollisionSolver
{
	public:
		CollisionSolver(std::function<void(PhysicBody&, PhysicBody&)> callback_collision);

		std::vector< bool > checkCollision(const std::vector< PhysicBody* >& bodies, const std::vector< PhysicParticle >& newParticles);

	private:
		std::function<void(PhysicBody&, PhysicBody&)> m_callbackCollision;
};
