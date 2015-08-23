#include "physicinstance.hpp"
#include "physicparticle.hpp"
#include "physicbody.hpp"
#include "collisionsolver.hpp"


PhysicInstance::PhysicInstance(CollisionSolver& collisionSolver) :
	m_collisionSolver(&collisionSolver)
{

}

void PhysicInstance::update(sf::Time time, sf::Time step)
{
	// TODO : step

	std::vector<PhysicParticle> particles;
	particles.resize(m_bodies.size());
	auto body = m_bodies.begin();
	auto particle = particles.begin();
	for (;body != m_bodies.end(); ++body, ++particle)
	{
		particle->position = (*body)->getParticle().position + time.asSeconds()*(*body)->getParticle().speed;
	}
	m_collisionSolver->checkCollision(m_bodies, particles); // TODO: apply movement
}

