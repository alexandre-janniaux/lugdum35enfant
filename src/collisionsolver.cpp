#include "collisionsolver.hpp"
#include <assert.h>

#include "physicbody.hpp"

CollisionSolver::CollisionSolver(std::function< void(PhysicBody&,PhysicBody&) > callback_collision) :
	m_callbackCollision(callback_collision)
{

}


void CollisionSolver::checkCollision(const std::vector< PhysicBody* >& bodies, const std::vector< PhysicParticle >& newParticles)
{
	assert(bodies.size() == newParticles.size());
	auto body = bodies.begin();
	auto particle = newParticles.begin();

	while (body != bodies.end())
	{
		auto body2 = body + 1;
		auto particle2 = particle + 1;

		while (body2 != bodies.end())
		{
			float r1 = (*body)->getCirconscritRadius();
			float r2 = (*body2)->getCirconscritRadius();

			auto vec = particle->position - particle2->position;
			auto d = vec.x*vec.x + vec.y*vec.y;
			if (d < (r1+r2)*(r1+r2)) {
				// TODO test SAT
				m_callbackCollision(**body, **body2);
			}
		}
		++body;
		++particle;
	}
}

