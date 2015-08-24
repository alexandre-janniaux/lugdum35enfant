#include "physicbody.hpp"
#include "physicgeom.hpp"
#include "scenenode.hpp"
#include "physicinstance.hpp"

PhysicBody::PhysicBody(Entity entity)
{
	m_type = 1;
	m_entity = entity;
	m_node = nullptr;
}


float PhysicBody::getCirconscritRadius()
{

}

bool PhysicBody::isFrozen() const
{
	return m_freeze;
}

void PhysicBody::setFreeze(bool freeze)
{
	m_freeze = freeze;
}

void PhysicBody::setNode(SceneNode* node)
{
	m_node = node;
}

SceneNode* PhysicBody::getNode() const
{
	return m_node;
}


std::size_t PhysicBody::getType() const
{
	return m_type;
}


void PhysicBody::setType(std::size_t type)
{
	m_type = type;
}

const sf::Vector2f& PhysicBody::getSpeed() const
{
	return m_speed;
}

void PhysicBody::setSpeed(const sf::Vector2f& speed)
{
	std::cout << "set speed = " << speed.x << "/" << speed.y << std::endl;
	m_speed = speed;
}


void PhysicBody::setPosition(const sf::Vector2f& position)
{
	if (m_node) {
		m_node->setPosition(position);//setAbsolutePosition(position);
	} else{
		std::cout << "Not assigned node" << std::endl;
	}
}

sf::Vector2f PhysicBody::getPosition() const
{
	if (m_node)
		return m_node->getAbsolutePosition();
	std::cout << "No node assigned" << std::endl;
	return sf::Vector2f(0,0);
}

const sf::FloatRect& PhysicBody::getHitbox() const
{
	return m_hitBox;
}

void PhysicBody::setHitbox(const sf::FloatRect& rect)
{
	m_hitBox = rect;
}



Entity PhysicBody::getRelatedEntity()
{
	return m_entity;
}
