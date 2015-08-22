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
	sprite.setSize(sf::Vector2f(40, 40));
	sprite.setFillColor(sf::Color::Red);
	sprite.setPosition(pos - sf::Vector2f(20, 20));
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


const float TIME_SPEED = 1;
void GameScreenState::update(const sf::Time& time) {
	float s = time.asSeconds() * TIME_SPEED;
	sf::Vector2f offset = velocity * s + ((float) 0.5) * s * s * acceleration;
	pos += offset;
	m_view.move(offset);
	sf::Vector2f oldv = velocity + ((float) 0.5) * s * acceleration;
	velocity += s * acceleration;
	acceleration = sf::Vector2f(0, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		velocity.x = std::min(velocity.x + (float)800 * s, (float)200);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		velocity.x = std::max(velocity.x - (float)800 * s, (float)-200);
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		velocity.y = std::min(velocity.y + (float)800 * s, (float)200);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		velocity.y = std::max(velocity.y - (float)800 * s, (float)-200);
	}
	
	velocity.x = std::max(std::min(velocity.x, (float)1500), (float)-1500);
	velocity.y = std::max(std::min(velocity.y, (float)1500), (float)-1500);
	rectangle me_ex = rectangle(pos - sf::Vector2f(20, 19.9), pos + sf::Vector2f(20, 19.9));
	rectangle me_ey = rectangle(pos - sf::Vector2f(19.9, 20), pos + sf::Vector2f(19.9, 20));
	rectangle me = rectangle(pos - sf::Vector2f(20, 20), pos + sf::Vector2f(20, 20));
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
				touching_walls[LEFT] = std::max(touching_walls[LEFT], (unsigned char)1);
			}
			if (me_ey.maxp.x <= level.boxes[i].maxp.x) {
				touching_walls[RIGHT] = std::max(touching_walls[RIGHT], (unsigned char)1);
			}
		}
		if (level.boxes[i].intersects(me_ey)) {
			if (me_ex.minp.y >= level.boxes[i].minp.y) {
				touching_walls[TOP] = std::max(touching_walls[TOP], (unsigned char)1);
			}
			if (me_ex.maxp.y <= level.boxes[i].maxp.y) {
				touching_walls[BOTTOM] = std::max(touching_walls[BOTTOM], (unsigned char)1);
			}
		}
	}
	switch (touching_walls[LEFT]) {
		case 1:
			velocity.x = std::max(velocity.x, (float)0);
			acceleration.x = std::max(acceleration.x, (float)0);
			break;
		default: break;
	}
	switch (touching_walls[RIGHT]) {
		case 1:
			velocity.x = std::min(velocity.x, (float)0);
			acceleration.x = std::min(acceleration.x, (float)0);
			break;
		default: break;
	}
	switch (touching_walls[TOP]) {
		case 1:
			velocity.y = std::max(velocity.y, (float)0);
			acceleration.y = std::max(acceleration.y, (float)0);
			break;
		default: break;
	}
	switch (touching_walls[BOTTOM]) {
		case 1:
			velocity.y = std::min(velocity.y, (float)0);
			acceleration.y = std::min(acceleration.y, (float)0);
			break;
		default: break;
	}
 
	velocity.x *= pow(0.01, s);
	velocity.y *= pow(0.01, s);
}

void GameScreenState::window_update(const sf::RenderWindow& window)
{
}
