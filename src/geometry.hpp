#pragma once

#include <SFML/Graphics.hpp>
#include <vector>


const float epsilon = 1e-3f;
inline bool check(const float &x) {
	return -epsilon <= x && x <= 1.f + epsilon;
}

inline bool check_strict(const float &x) {
	return epsilon <= x && x <= 1.f - epsilon;
}

inline sf::Vector2f interp(const sf::Vector2f p1, const sf::Vector2f p2, float t) {
	return (1.f - t) * p1 + t * p2;
}

struct Segment {
	sf::Vector2f p1, p2;
	Segment();
	Segment(sf::Vector2f, sf::Vector2f);
	const sf::Vector2f intersection_time(const Segment &other) const;
	const sf::Vector2f intersection(const Segment &other) const;
	void intersection_triangle(const sf::Vector2f lumiere, const Segment &tri, std::vector<Segment> &result);
};

