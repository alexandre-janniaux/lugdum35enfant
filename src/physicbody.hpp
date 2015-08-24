#pragma once

#include "physicparticle.hpp"

#include <vector>
#include <memory>

class PhysicGeom;
class SceneNode;

class PhysicBody
{
	public:
		PhysicBody();

		float getCirconscritRadius();
		void setFreeze(bool freeze);
		bool isFrozen() const;

		std::size_t getType() const;
		void setType(std::size_t type);

		SceneNode* getNode() const;
		void setNode(SceneNode* node);

		const sf::Vector2f& getSpeed() const;
		void setSpeed(const sf::Vector2f& speed);

		void setPosition(const sf::Vector2f& position);

		//const PhysicParticle& getParticle() const;
	private:
		SceneNode* m_node;
		std::vector<std::unique_ptr<PhysicGeom>> m_geoms;
		std::size_t m_type;
		sf::Vector2f m_speed;
		bool m_freeze;

};
