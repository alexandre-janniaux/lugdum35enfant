#include "hero.hpp"
#include "gameworld.hpp"
#include "entitypool.hpp"
#include "physicinstance.hpp"
#include "entityscene.hpp"
#include "messagebus.hpp"
#include "gamemessage.hpp"
#include "resourcemanager.hpp"

Hero::Hero() :
	m_sprite(make_unique<SpriteSceneNode>(15))
{

	m_sprite->setTexture(TextureManager::instance()->get("graphics/furniture/shelf1.png"));
	//m_sprite.setPosition(m_sprite.);
	m_speed = 10.f;
}

Hero::~Hero() {
	m_entity.pool->kill(m_entity);
}


Hero* Hero::createHero(GameContext& context)
{
	assert(context.scene != nullptr);
	assert(context.entityPool != nullptr);
	assert(context.physic != nullptr);

	Hero* hero = new Hero;
	hero->m_entity = context.entityPool->createEntity();
	auto& node = context.scene->bindEntity(hero->m_entity);
	auto& body = context.physic->bindEntity(hero->m_entity);
	body.setNode(&node);

	hero->m_sprite->attachParent(node);
	return hero;
}

void Hero::move(int direction)
{
	sf::Vector2f speed {0.f, 0.f};
	if (! direction & Hero::TOP & Hero::BOTTOM) {
		if (direction & Hero::TOP) speed += {0.f, -1.f};
		else if (direction & Hero::BOTTOM) speed += {0.f, 1.f};
	}
	if (! direction & Hero::LEFT & Hero::RIGHT) {
		if (direction & Hero::LEFT) speed += {-1.f, 0.f};
		else if (direction & Hero::RIGHT) speed += {1.f, 0.f};
	}

	if (speed != sf::Vector2f(0.f, 0.f)) {
		speed /= std::sqrt(speed.x*speed.x + speed.y*speed.y);
		speed *= m_speed;
		SendMessage(SetEntitySpeedMessage({m_entity, speed}));
	}
}

void Hero::setPosition(const sf::Vector2f& position)
{
	SendMessage(SetEntityPositionMessage({m_entity, position}));
}
