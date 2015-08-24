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
			TOP = 		0b0001,
			BOTTOM = 	0b0010,
			LEFT = 		0b0100,
			RIGHT = 	0b1000
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
