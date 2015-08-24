#include "hero.hpp"
#include "gameworld.hpp"
#include "entitypool.hpp"
#include "physicinstance.hpp"
#include "entityscene.hpp"
#include "messagebus.hpp"
#include "gamemessage.hpp"
#include "resourcemanager.hpp"
#include <cmath>

Hero::Hero() :
	m_sprite(make_unique<SpriteSceneNode>(15))
{

	m_sprite->setTexture(TextureManager::instance()->get("graphics/furniture/shelf1.png"));
	//m_sprite.setPosition(m_sprite.);
	m_speed = 60.f;
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
	auto node = context.scene->bindEntity(hero->m_entity);
	auto body = context.physic->bindEntity(hero->m_entity);
	body->setNode(node);
	body->setHitbox(hero->m_sprite->getSprite().getLocalBounds());
	node->setPosition({15.f,60.f});

	hero->m_sprite->attachParent(*node);
	return hero;
}

void Hero::move(int direction)
{

	sf::Vector2i speed {0, 0};

	if (direction & Hero::TOP) 		speed += {0, -1};
	if (direction & Hero::BOTTOM) 	speed += {0, 1};
	if (direction & Hero::LEFT) 	speed += {-1, 0};
	if (direction & Hero::RIGHT)  	speed += {1, 0};


	if (speed.x == 0 && speed.y == 0) {
		SendMessage(SetEntitySpeedMessage({m_entity, sf::Vector2f(0.f,0.f)}));
	}
	else {
		auto norme = std::sqrt(speed.x*speed.x + speed.y*speed.y);
		SendMessage(SetEntitySpeedMessage({m_entity, m_speed*sf::Vector2f(((float)speed.x)/norme, ((float)speed.y)/norme)}));
	}
}

void Hero::setPosition(const sf::Vector2f& position)
{
	SendMessage(SetEntityPositionMessage({m_entity, position}));
}
