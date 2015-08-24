#pragma once

#include "entitypool.hpp"
#include <memory>
#include "spritescenenode.hpp"

class GameContext;


class Hero
{
	public:

		enum Direction {
			NONE = 		0,
			TOP = 		1 << 0,
			BOTTOM = 	1 << 1,
			LEFT = 		1 << 2,
			RIGHT = 	1 << 3
		};

		static std::unique_ptr<Hero> createHero(GameContext& context);

		void move(Direction direction);

	private:
		Hero();
		float m_speed;
		SpriteSceneNode m_sprite;
		Entity m_entity;

};
