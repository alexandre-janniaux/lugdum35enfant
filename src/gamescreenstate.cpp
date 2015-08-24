#include "gamescreenstate.hpp"
#include "hero.hpp"
#include "messagebus.hpp"
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <functional>

//const int TOP = 1;
//const int BOTTOM = 2;
//const int LEFT = 4;
//const int RIGHT = 8;
const unsigned char TOP = 0;
const unsigned char BOTTOM = 1;
const unsigned char LEFT = 2;
const unsigned char RIGHT = 3;

const float TIME_SPEED = 1;
const float KEY_ACCEL = 800;
const float MAX_SPEED = 200;
const float PERSO_SIZE = 20;
const float AIR_VISC = 0.01;
const float SOLID_ACCEL = 200;


inline float clamp(float x, float min, float max) {
	 return std::max(std::min(x, max), min);
}

GameScreenState::GameScreenState(sf::RenderWindow* window) :
	m_collisionSolver([this](PhysicBody& b1, PhysicBody& b2){this->onCollision(b1, b2);}),
	m_physicInstance(m_collisionSolver),
	m_world(nullptr)
{
	m_context.entityPool = &m_entityPool;
	m_context.physic = &m_physicInstance;
	m_context.scene = &m_scene;
	m_context.window = window;

	m_world.reset(new GameWorld(m_context, "", m_context.scene->getRootNode()));

	m_hero = Hero::createHero(m_context);
}

void GameScreenState::event(const sf::RenderTarget& target, const sf::Event& event) {
	switch(event.type)
	{
		case sf::Event::KeyPressed:
			break;

		case sf::Event::KeyReleased:
			break;

		default:
			break;
	}

}


void GameScreenState::updateView(sf::RenderTarget& target) {
	sf::Vector2f size = (sf::Vector2f)target.getSize();
	sf::Vector2f center; // TODO center upon the player
	//m_view.setCenter(center);
	m_view.setSize(size);
	target.setView(m_view);
}

void GameScreenState::render(sf::RenderTarget& target) {
	target.draw(m_scene);
}

void GameScreenState::update(const sf::Time& time) {
	// TODO: Dynamic keyboard configuration
	int direction;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		direction |= Hero::LEFT;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		direction |= Hero::RIGHT;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		direction |= Hero::TOP;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		direction |= Hero::BOTTOM;

	m_hero->move(direction);

	m_physicInstance.update(time, sf::seconds(0.1f));
}

void GameScreenState::window_update(const sf::RenderWindow& window)
{
}

void GameScreenState::onCollision(PhysicBody& b1, PhysicBody& b2)
{

}
