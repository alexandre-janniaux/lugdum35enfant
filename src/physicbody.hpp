#pragma once

#include "physicparticle.hpp"

#include <vector>
#include <memory>

class PhysicGeom;

class PhysicBody
{
	public:

		float getCirconscritRadius();
		void setFreeze();
		bool isFrozen() const;

		const PhysicParticle& getParticle() const;
	private:
		PhysicParticle m_particle;
		std::vector<std::unique_ptr<PhysicGeom>> m_geoms;


};
