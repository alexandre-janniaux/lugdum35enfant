#pragma once

#include "physicparticle.hpp"

#include <vector>
#include <memory>

class PhysicGeom;

class PhysicBody
{
	public:
		PhysicBody();

		float getCirconscritRadius();
		void setFreeze();
		bool isFrozen() const;

		std::size_t getType() const;
		void setType(std::size_t type);

		void setPosition(const sf::Vector2f& position);

		const PhysicParticle& getParticle() const;
	private:
		PhysicParticle m_particle;
		PhysicParticle m_future;
		std::vector<std::unique_ptr<PhysicGeom>> m_geoms;
		std::size_t m_type;


};
