#include "physicbody.hpp"
#include "physicgeom.hpp"

PhysicBody::PhysicBody()
{
	m_type = 1;
}


float PhysicBody::getCirconscritRadius()
{

}

bool PhysicBody::isFrozen() const
{

}

void PhysicBody::setFreeze()
{

}
const PhysicParticle& PhysicBody::getParticle() const
{
	return m_particle;
}

std::size_t PhysicBody::getType() const
{
	return m_type;
}


void PhysicBody::setType(std::size_t type)
{
	m_type = type;
}

void PhysicBody::setPosition(const sf::Vector2f& position)
{
	m_particle.position = position;
}
