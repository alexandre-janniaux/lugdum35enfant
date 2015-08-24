#include "physicinstance.hpp"
#include "physicparticle.hpp"
#include "physicbody.hpp"
#include "collisionsolver.hpp"
#include "scenenode.hpp"
#include "cpp_std_11.hpp"
#include <utility>

PhysicInstance::PhysicInstance(CollisionSolver& collisionSolver) :
	m_collisionSolver(&collisionSolver)
{
}

PhysicBody& PhysicInstance::bindEntity(Entity entity)
{
	auto search = m_bodiesOwned.find(entity);
	if (search == m_bodiesOwned.end())
	{
		auto body = new PhysicBody(entity);
		m_bodiesOwned.emplace(entity, body);
		m_bodies.push_back(body);
		return *body;
	}

	return *search->second;
}

void PhysicInstance::unbindEntity(Entity entity)
{
	auto search = m_bodiesOwned.find(entity);
	if (search != m_bodiesOwned.end())
	{
		m_bodies.erase(std::find(m_bodies.begin(), m_bodies.end(), search->second));
		m_bodiesOwned.erase(search);
	}
}


void PhysicInstance::update(sf::Time time, sf::Time step)
{
	// TODO : step

	std::vector<sf::Vector2f> particles;
	particles.resize(m_bodies.size());
	auto body = m_bodies.begin();
	auto particle = particles.begin();
	for (;body != m_bodies.end(); ++body, ++particle)
	{
		*particle = (*body)->getNode()->getAbsolutePosition() + time.asSeconds()*(*body)->getSpeed();
	}
	std::vector<bool> collisions = m_collisionSolver->checkCollision(m_bodies, particles); // TODO: apply movement

	for(int i=0; i<collisions.size(); ++i) {
		if (!collisions[i])
			m_bodies[i]->setPosition(particles[i]);
	}
}

