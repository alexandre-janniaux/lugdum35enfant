#include "collisionsolver.hpp"
#include <assert.h>
#include <iostream>
#include <SFML/Graphics/Rect.hpp>

#include "physicbody.hpp"

CollisionSolver::CollisionSolver(std::function< void(PhysicBody&,PhysicBody&) > callback_collision) :
	m_callbackCollision(callback_collision)
{

}


std::vector<bool> CollisionSolver::checkCollision(const std::vector< PhysicBody* >& bodies, const std::vector< sf::Vector2f>& newParticles)
{
	assert(bodies.size() == newParticles.size());

	std::vector<bool> collisions;
	collisions.resize(bodies.size(), false);

	for (int i=0; i < bodies.size()-1; ++i)
	{
		for(int j=i+1; j < bodies.size(); ++j)
		{
			auto& body = *bodies[i];
			auto& body2 = *bodies[j];
			auto& particle = newParticles[i];
			auto& particle2 = newParticles[j];

			//float r1 = body.getCirconscritRadius();
			//float r2 = body2.getCirconscritRadius();

			//auto vec = particle - particle2;
			//auto d = vec.x*vec.x + vec.y*vec.y;

			sf::FloatRect hitbox1 = body.getHitbox();
			hitbox1.left += body.getPosition().x;
			hitbox1.top  += body.getPosition().y;

			sf::FloatRect hitbox2 = body2.getHitbox();
			hitbox2.left += body2.getPosition().x;
			hitbox2.top  += body2.getPosition().y;


			if (hitbox1.intersects(hitbox2)) {

				if ((body.getType() & body2.getType()) != 0) {
					collisions[i] = collisions[j] = true;
				}
				// TODO test SAT
				m_callbackCollision(body, body2);

			}
		}
	}
	return collisions;
}

