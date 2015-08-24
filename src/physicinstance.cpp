#include "physicinstance.hpp"
#include "physicparticle.hpp"
#include "physicbody.hpp"
#include "collisionsolver.hpp"
#include "scenenode.hpp"
#include "cpp_std_11.hpp"
#include <utility>
#include <functional>

using namespace std::placeholders;

PhysicInstance::PhysicInstance(CollisionSolver& collisionSolver) :
	m_collisionSolver(&collisionSolver),
	m_entitySpeedMessage(std::bind(&PhysicInstance::onSetEntitySpeedMessage, this, _1)),
	m_entityPositionMessage(std::bind(&PhysicInstance::onSetEntityPositionMessage, this, _1))
{
}

PhysicBody& PhysicInstance::bindEntity(Entity entity)
{
	auto search = m_bodiesOwned.find(entity);
	if (search == m_bodiesOwned.end())
	{
		m_bodiesOwned.emplace(entity, std::unique_ptr<PhysicBody>(new PhysicBody(entity)));
		PhysicBody* body = m_bodiesOwned.at(entity).get();
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
		m_bodies.erase(std::find(m_bodies.begin(), m_bodies.end(), search->second.get()));
		m_bodiesOwned.erase(search);
	}
}


void PhysicInstance::update(sf::Time time, sf::Time step)
{
	// TODO : step

	std::vector<sf::Vector2f> particles;
	particles.resize(m_bodies.size());
	for (std::size_t i=0; i < m_bodies.size(); ++i)
	{
		std::cout << "Position : " << m_bodies[i]->getPosition().x << "/" << m_bodies[i]->getPosition().y << std::endl;
		particles[i] = m_bodies[i]->getNode()->getAbsolutePosition() + time.asSeconds()*m_bodies[i]->getSpeed();
	}
	const std::vector<bool>& collisions = m_collisionSolver->checkCollision(m_bodies, particles); // TODO: apply movement

	for(int i=0; i<collisions.size(); ++i) {
		if (!collisions[i])
			m_bodies[i]->setPosition(particles[i]);
	}

	m_entitySpeedMessage.readAll();
}

void PhysicInstance::onSetEntitySpeedMessage(const SetEntitySpeedMessage& message)
{
	static std::size_t nb = 0;
	std::cout << "SpeedMessageEntity nb [" << nb++ << "]entity : " << message.entity.id << std::endl;

	auto search = m_bodiesOwned.find(message.entity);
	if (search != m_bodiesOwned.end()) {
		auto& body = *search->second;
		std::cout << "Position : " << body.getPosition().x << "/" << body.getPosition().y << std::endl;
		std::cout << "Speed : " << body.getSpeed().x << "/" << body.getSpeed().y << std::endl;
		search->second->setSpeed(message.speed);
	}
}

void PhysicInstance::onSetEntityPositionMessage(const SetEntityPositionMessage& message)
{
	auto search = m_bodiesOwned.find(message.entity);
	if (search != m_bodiesOwned.end()) {
		auto& body = *search->second;
		std::cout << "Position : " << body.getPosition().x << "/" << body.getPosition().y << std::endl;
		std::cout << "Speed : " << body.getSpeed().x << "/" << body.getSpeed().y << std::endl;
		search->second->setPosition(message.position);
	}
}
