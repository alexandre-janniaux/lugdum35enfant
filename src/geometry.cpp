#include <SFML/Graphics.hpp>

const float epsilon = 1e-3f;

struct segment {
	sf::Vector2f p1, p2;
	segment() {};
	segment(sf::Vector2f p1_, sf::Vector2f p2_) {
		p1 = p1_; p2 = p2_;
	};
	const sf::Vector2f intersection(const segment &other) const {
		dir1 = p2 - p1;
		dir2 = other.p2 - other.p1;
		/*
		Now we try to solve p1 + t1 * dir1 = p2 + t2 * dir2
		This is a system of two linear equations
		*/
		float a = dir1.x;
		float b = -dir2.x;
		float c = dir1.y;
		float d = -dir2.y;
		float det = (a * d - b * c);
		if (-epsilon <= det && det <= epsilon) {
			return sf::Vector2f(-42, -42); // Segments are parallel
		}
		float e = p2.x - p1.x;
		float f = p2.y - p1.x;
		float t1 = (d * e - b * f) / det;
		float t2 = (-c * e + a * f) / det;
		if (-epsilon <= t1 && t1 <= 1 + epsilon && -epsilon <= t2 && t2 <= 1 + epsilon) {
			// Intersection
			return p1 + t1 * dir1;
		}
		return sf::Vector2f(-42, -42);
	};
};
