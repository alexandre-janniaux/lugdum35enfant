#pragma once

#include "physicparticle.hpp"
#include "entitypool.hpp"

#include <vector>
#include <memory>

#include "physicgeom.hpp"

//class PhysicGeom;
class SceneNode;
class PhysicInstance;

class PhysicBody
{
	public:


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
		sf::Vector2f getPosition() const;

		void setHitbox(const sf::FloatRect& rect);
		const sf::FloatRect& getHitbox() const;

		Entity getRelatedEntity();
	private:
		friend class PhysicInstance;
		PhysicBody(Entity entity);

		Entity m_entity;
		SceneNode* m_node;
		sf::FloatRect m_hitBox;
		std::size_t m_type;
		sf::Vector2f m_speed;
		bool m_freeze;

};
