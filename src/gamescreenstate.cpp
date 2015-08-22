#include "gamescreenstate.hpp"
#include <algorithm>
#include <SFML/Graphics.hpp>

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

GameScreenState::GameScreenState() {

}

void GameScreenState::event(const sf::RenderTarget& target, const sf::Event& event) {
}


void GameScreenState::updateView(sf::RenderTarget& target) {
	sf::Vector2f size = (sf::Vector2f)target.getSize();
	sf::Vector2f center; // TODO center upon the player
	//m_view.setCenter(center);
	m_view.setSize(size);
	target.setView(m_view);
}

void GameScreenState::render(sf::RenderTarget& target) {

}

void GameScreenState::update(const sf::Time& time) {
	
}

void GameScreenState::window_update(const sf::RenderWindow& window)
{
}
