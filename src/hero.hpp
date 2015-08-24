#pragma once

#include "entitypool.hpp"
#include <memory>
#include "spritescenenode.hpp"

class GameContext;


class Hero
{
	public:
		~Hero();

		enum Direction {
			NONE = 		0,
			TOP = 		1 << 0,
			BOTTOM = 	1 << 1,
			LEFT = 		1 << 2,
			RIGHT = 	1 << 3
		};

		static Hero* createHero(GameContext& context);

		void move(int direction);

		void setPosition(const sf::Vector2f& position);

		
	private:
		Hero();
		float m_speed;
		std::unique_ptr<SpriteSceneNode> m_sprite;
		Entity m_entity;

};
