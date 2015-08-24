#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

using V2d = sf::Vector2<double>;


inline sf::Vector2f d2f(V2d vectorD)
{
    return sf::Vector2f(vectorD.x,vectorD.y);
}

inline V2d f2d(sf::Vector2f vectorF)
{
    return V2d((double)vectorF.x,(double)vectorF.y);
}

const double epsilon = 1e-9f;
inline bool check(const double &x) {
	return -epsilon <= x && x <= 1.f + epsilon;
}

inline bool check_strict(const double &x) {
	return epsilon <= x && x <= 1.f - epsilon;
}

inline V2d interp(const V2d p1, const V2d p2, double t) {
	return (1.f - t) * p1 + t * p2;
}

struct Segment {
	V2d p1, p2;
	Segment();
	Segment(V2d, V2d);
	const V2d intersection_time(const Segment &other) const;
	const V2d intersection_droites(const Segment &other) const;
	const V2d intersection(const Segment &other) const;
	void intersection_triangle(const V2d, const Segment &tri, std::vector<Segment> &result);
};
