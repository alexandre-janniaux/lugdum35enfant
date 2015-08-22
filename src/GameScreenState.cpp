#include "GameScreenState.h"
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
	advancement = 0;
	level = Level("./example.lvl");
	resetPos();
	updateSprites();
}

void GameScreenState::resetPos() {
	pos = level.check_pos[advancement];
	velocity = sf::Vector2f(0, 0);
	acceleration = sf::Vector2f(0, 0);
	for (unsigned char i = 0; i < 4; i++) touching_walls[i] = 0;
}

void GameScreenState::event(const sf::RenderTarget& target, const sf::Event& event) {
}

void GameScreenState::updateSprites() {
	sprites.clear();
	sprites.resize(1);

	sf::RectangleShape sprite;
	sprite.setSize(sf::Vector2f(2 * PERSO_SIZE, 2 * PERSO_SIZE));
	sprite.setFillColor(sf::Color::Red);
	sprite.setPosition(pos - sf::Vector2f(PERSO_SIZE, PERSO_SIZE));
	sprites.push_back(sprite);
}

void GameScreenState::updateView(sf::RenderTarget& target) {
	sf::Vector2f size = (sf::Vector2f)target.getSize();
	sf::Vector2f center
		(clamp(pos.x, level.bbox.minp.x + size.x / 2,
			level.bbox.maxp.x - size.x / 2),
		clamp(pos.y, level.bbox.minp.y + size.y / 2,
			level.bbox.maxp.y - size.y / 2));
	m_view.setCenter(center);
	m_view.setSize(size);
	target.setView(m_view);
}

void GameScreenState::render(sf::RenderTarget& target) {
	updateSprites();
	updateView(target);
	target.clear(sf::Color::White);
	level.render(target);
	for (unsigned int i = 0; i < sprites.size(); i++) {
		target.draw(sprites[i]);
	}
}

void GameScreenState::update(const sf::Time& time) {
	float s = time.asSeconds() * TIME_SPEED;
	sf::Vector2f offset = velocity * s + 0.5f * s * s * acceleration;
	pos += offset;
	m_view.move(offset);
	sf::Vector2f oldv = velocity + 0.5f * s * acceleration;
	velocity += s * acceleration;
	acceleration = sf::Vector2f(0, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		velocity.x += KEY_ACCEL * s;
    }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		velocity.x -= KEY_ACCEL * s;
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		velocity.y += KEY_ACCEL * s;
    }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		velocity.y -= KEY_ACCEL * s;
	}
	velocity.x = clamp(velocity.x, -MAX_SPEED, MAX_SPEED);
	velocity.y = clamp(velocity.y, -MAX_SPEED, MAX_SPEED);
	
	rectangle me_ex = rectangle(pos - sf::Vector2f(PERSO_SIZE, PERSO_SIZE - 0.1f), pos + sf::Vector2f(PERSO_SIZE, PERSO_SIZE - 0.1f));
	rectangle me_ey = rectangle(pos - sf::Vector2f(PERSO_SIZE - 0.1f, PERSO_SIZE), pos + sf::Vector2f(PERSO_SIZE - 0.1f, PERSO_SIZE));
	rectangle me = rectangle(pos - sf::Vector2f(PERSO_SIZE, PERSO_SIZE), pos + sf::Vector2f(PERSO_SIZE, PERSO_SIZE));
	for (unsigned char i = 0; i < 4; i++) touching_walls[i] = 0;
	for (unsigned int i = 0; i < level.boxes.size(); i++) {
		if (level.boxes[i].intersects(me_ex)) {
			if (me_ey.maxp.x >= level.boxes[i].maxp.x) {
				if (me_ey.minp.x >= level.boxes[i].maxp.x + oldv.x * s) {
					float d = std::max(level.boxes[i].maxp.x - me_ex.minp.x, (float)0);
					pos.x += d;
					m_view.move(d,0);
					me_ex.movex(d);
					me_ey.movex(d);
				}
			}
			if (me_ey.minp.x <= level.boxes[i].minp.x) {
				if (me_ey.maxp.x <= level.boxes[i].minp.x + oldv.x * s) {
					float d = std::min(level.boxes[i].minp.x - me_ex.maxp.x, (float)0);
					pos.x += d;
					m_view.move(d,0);
					me_ex.movex(d);
					me_ey.movex(d);
				}
			}
		}
		if (level.boxes[i].intersects(me_ey)) {
			if (me_ex.maxp.y >= level.boxes[i].maxp.y) {
				if (me_ex.minp.y >= level.boxes[i].maxp.y + oldv.y * s) {
					float d = std::max(level.boxes[i].maxp.y - me_ey.minp.y, (float)0);
					pos.y += d;
					m_view.move(0.f,d);
					me_ex.movey(d);
					me_ey.movey(d);
				}
			}
			if (me_ex.minp.y <= level.boxes[i].minp.y) {
				if (me_ex.maxp.y <= level.boxes[i].minp.y + oldv.y * s) {
					float d = std::min(level.boxes[i].minp.y - me_ey.maxp.y, (float)0); 
					pos.y += d;
					m_view.move(0.f,d);
					me_ex.movey(d);
					me_ey.movey(d);
				}
			}
		}
	}
	
	for (unsigned int i = 0; i < level.boxes.size(); i++) {
		if (level.boxes[i].intersects(me_ex)) {
			if (me_ey.minp.x >= level.boxes[i].minp.x) {
				velocity.x = std::max(velocity.x, 0.f);
				acceleration.x = std::max(acceleration.x, 0.f);
			}
			if (me_ey.maxp.x <= level.boxes[i].maxp.x) {
				velocity.x = std::min(velocity.x, 0.f);
				acceleration.x = std::min(acceleration.x, 0.f);
			}
		}
		if (level.boxes[i].intersects(me_ey)) {
			if (me_ex.minp.y >= level.boxes[i].minp.y) {
				velocity.y = std::max(velocity.y, 0.f);
				acceleration.y = std::max(acceleration.y, 0.f);
			}
			if (me_ex.maxp.y <= level.boxes[i].maxp.y) {
				velocity.y = std::min(velocity.y, 0.f);
				acceleration.y = std::min(acceleration.y, 0.f);
			}
		}
	}
 
	velocity.x *= pow(AIR_VISC, s);
	if (velocity.x >= 0) {
		velocity.x = std::max(velocity.x - SOLID_ACCEL * s, 0.f);
	} else {
		velocity.x = std::min(velocity.x + SOLID_ACCEL * s, 0.f);
	}
	velocity.y *= pow(AIR_VISC, s);
	if (velocity.y >= 0) {
		velocity.y = std::max(velocity.y - SOLID_ACCEL * s, 0.f);
	} else {
		velocity.y = std::min(velocity.y + SOLID_ACCEL * s, 0.f);
	}
}

void GameScreenState::window_update(const sf::RenderWindow& window)
{
}
