#include "hero.hpp"
#include "gameworld.hpp"
#include "entitypool.hpp"
#include "physicinstance.hpp"
#include "entityscene.hpp"
#include "messagebus.hpp"
#include "gamemessage.hpp"
#include "resourcemanager.hpp"

Hero::Hero() :
	m_sprite(15)
{
	m_sprite.setTexture(TextureManager::instance()->get("graphics/shelf1.png"));
	//m_sprite.setPosition(m_sprite.);
	m_speed = 10.f;
}


std::unique_ptr<Hero> Hero::createHero(GameContext& context)
{
	assert(context.scene != nullptr);
	assert(context.entityPool != nullptr);
	assert(context.physic != nullptr);

	auto hero = std::unique_ptr<Hero>(new Hero);
	hero->m_entity = context.entityPool->createEntity();
	auto& node = context.scene->bindEntity(hero->m_entity);
	auto& body = context.physic->bindEntity(hero->m_entity);
	hero->m_sprite.attachParent(node);
	return hero;
}

void Hero::move(Hero::Direction direction)
{
	sf::Vector2f speed;
	if (direction & Hero::TOP) speed += {0.f, -1.f};
	if (direction & Hero::BOTTOM) speed += {0.f, 1.f};
	if (direction & Hero::LEFT) speed += {-1.f, 0.f};
	if (direction & Hero::RIGHT) speed += {1.f, 0.f};

	speed /= std::sqrt(speed.x*speed.x + speed.y*speed.y);
	speed *= m_speed;

	SendMessage(SetEntitySpeedMessge({m_entity, }));
}

