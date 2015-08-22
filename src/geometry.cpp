#include <SFML/Graphics.hpp>

const float epsilon = 1e-3f;

inline bool check(const float &x) {
	return -epsilon <= x && x <= 1.f + epsilon;
}

inline sf::Vector2f interp(const sf::Vector2f p1, const sf::Vector2f p2, float t) {
	return (1.f - t) * p1 + t * p2;
}

struct segment {
	sf::Vector2f p1, p2;
	segment() {};
	segment(sf::Vector2f p1_, sf::Vector2f p2_) {
		p1 = p1_; p2 = p2_;
	};
	const sf::Vector2f intersection_time(const segment &other) const {
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
		return sf::Vector2f(t1, t2);
	}
	const sf::Vector2f intersection(const segment &other) const {
		sf::Vector2f it = intersection_time(other);
		if (check(it.x) && check(it.y)) {
			// Intersection
			return interp(p1, p2, it.x);
		}
		return sf::Vector2f(-42, -42);
	};
	int intersection_triangle(const segment &tri1, const segment &tri2) {
		it1 = intersection_time(tri1);
		it2 = intersection_time(tri2);
		it3 = intersection_time(segment(tri1.p2, tri2.p2));
		segment seg1 = segment(tri1.p1, interp(tri1.p1, tri1.p2, it1.y));
		segment seg2 = segment(tri2.p1, interp(tri2.p1, tri2.p2, it2.y));
		segment seg3 = segment(tri1.p1, interp(tri1.p2, tri2.p2, it3.y));
			
		if (!(check(it1.y) || check(it2.y) || check(it3.y))) {
			// La droite du segment ne passe pas dans le triangle
			return 0;
		}
		if (!check(it3.y)) { 
			// La droite coupe les deux cotes principaux
			float u, v;
			sf::Vector2f pp1, pp2;
			if (it1.x < it2.x) {
				pp1 = p1; pp2 = p2; u = it1.x; v = it2.x;
			} else {
				pp1 = p2; pp2 = p1; u = it2.x; v = it1.x;
			}
			//float u = it1.x;
			//float v = it2.x;
			if (v < -epsilon || u > 1.f + epsilon) {
				// Segment à l'extérieur du triangle
				return 0;
			}
			sf::Vector2f inter1 = segment(tri1.p2, tri2.p2).intersection(segment(tri1.p1, pp1));
			sf::Vector2f inter2 = segment(tri1.p2, tri2.p2).intersection(segment(tri1.p1, pp2));
			if (-epsilon <= u && v < 1.f + epsilon) {
				// Completement a l'interieur	
				// On découpe en:
				// tri1, segment(tri1.p1, inter1)
				// segment(tri1.p1, pp1), segment(tri1.p1, pp2)
				// segment(tri1.p1, inter2), tri2
				return 3;
			}
			// On intersecte un seul cote
			if (check(it1.x)) {
				// On intersecte cote 1
				// On decoupe en:
				// seg1, segment(tri1.p1, pp2);
				// segment(tri1.p1, inter2), tri2
				return 2;
			} else {
				// On intersecte cote 2
				// On decoupe en:
				// tri1, segment(tri1.p1, inter1)
				// segment(tri1.p1, seg2)
				return 2;
			}
		}
		// TODO: Les autres possibilitees (si on touche le bout)
	};
};


