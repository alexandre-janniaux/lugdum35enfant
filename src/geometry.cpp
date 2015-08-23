#include "geometry.hpp"

Segment::Segment()
{
    p1=sf::Vector2f(0.f,0.f);
    p2=sf::Vector2f(0.f,0.f);
}

Segment::Segment(sf::Vector2f pointA, sf::Vector2f pointB)
{
    p1=pointA;
    p2=pointB;
}

const sf::Vector2f Segment::intersection_time(const Segment &other) const
{
    auto dir1 = p2 - p1;
    auto dir2 = other.p2 - other.p1;
    /*
    Now we try to solve p1 + t1 * dir1 = other.p1 + t2 * dir2
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
    float e = other.p1.x - p1.x;
    float f = other.p1.y - p1.x;
    float t1 = (d * e - b * f) / det;
    float t2 = (-c * e + a * f) / det;
    return sf::Vector2f(t1, t2);
}

const sf::Vector2f Segment::intersection(const Segment &other) const {
    sf::Vector2f it = intersection_time(other);
    if (check(it.x) && check(it.y)) {
        // Intersection
        return interp(p1, p2, it.x);
    }
    return sf::Vector2f(-42, -42);
};

void Segment::intersection_triangle(const sf::Vector2f lumiere,
        const Segment &tri, std::vector<Segment> &result) {
    Segment tri1 = Segment(lumiere, tri.p1);
    Segment tri2 = Segment(lumiere, tri.p2);
    sf::Vector2f it1 = intersection_time(tri1);
    sf::Vector2f it2 = intersection_time(tri2);
    sf::Vector2f it3 = intersection_time(tri);
    sf::Vector2f si1 = interp(lumiere, tri.p1, it1.y);
    sf::Vector2f si2 = interp(lumiere, tri.p2, it2.y);
    sf::Vector2f si3 = interp(tri.p1, tri.p2, it3.y);

    if (!(check(it1.y) || check(it2.y) || check(it3.y))) {
        // La droite du segment ne passe pas dans le triangle
        result.push_back(tri);
        return;
    }

    if (!check_strict(it3.y)) {
        // La droite coupe les deux cotes principaux
        float u, v;
        sf::Vector2f pp1, pp2;
        if (it1.x < it2.x) {
            pp1 = p1; pp2 = p2; u = it1.x; v = it2.x;
        } else {
            pp1 = p2; pp2 = p1; u = it2.x; v = it1.x;
        }
        if (v < epsilon || u > 1.f - epsilon) {
            // Segment à l'extérieur du triangle
            result.push_back(tri);
            return;
        }
        sf::Vector2f inter1 = tri.intersection(Segment(lumiere, pp1));
        sf::Vector2f inter2 = tri.intersection(Segment(lumiere, pp2));
        if (-epsilon <= u && v < 1.f + epsilon) {
            // Completement a l'interieur
            result.push_back(Segment(tri.p1, inter1));
            result.push_back(Segment(pp1, pp2));
            result.push_back(Segment(inter2, tri.p2));
            return;
        }
        // On intersecte un seul cote
        if (check(it1.x)) {
            // On intersecte cote 1
            result.push_back(Segment(si1, pp2));
            result.push_back(Segment(inter2, tri.p2));
            return;
        } else {
            // On intersecte cote 2
            result.push_back(Segment(tri.p1, inter1));
            result.push_back(Segment(pp1, si2));
            return;
        }
    }

    if (!check_strict(it1.y)) {
        // On coupe cote 2 et le bout
        float u, v;
        sf::Vector2f pp1, pp2;
        if (it3.x < it2.x) {
            pp1 = p1; pp2 = p2; u = it3.x; v = it2.x;
        } else {
            pp1 = p2; pp2 = p1; u = it2.x; v = it3.x;
        }
        if (v < epsilon || u > 1.f - epsilon) {
            // Segment à l'extérieur du triangle
            result.push_back(tri);
            return;
        }
        sf::Vector2f inter1 = tri.intersection(Segment(lumiere, pp1));
        sf::Vector2f inter2 = tri.intersection(Segment(lumiere, pp2));
        if (-epsilon <= u && v < 1.f + epsilon) {
            // Completement a l'interieur
            result.push_back(Segment(tri.p1, inter1));
            result.push_back(Segment(pp1, pp2));
            result.push_back(Segment(inter2, tri.p2));
            return;
        }
        // On intersecte un seul cote
        if (check(it3.x)) {
            // On intersecte le bout
            result.push_back(Segment(tri.p1, si3));
            result.push_back(Segment(si3, pp2));
            result.push_back(Segment(inter2, tri.p2));
            return;
        } else {
            // On intersecte cote 2
            result.push_back(Segment(tri.p1, inter1));
            result.push_back(Segment(pp1, si2));
            return;
        }
    } else {
        // On coupe cote 1 et le bout
        float u, v;
        sf::Vector2f pp1, pp2;
        if (it1.x < it3.x) {
            pp1 = p1; pp2 = p2; u = it1.x; v = it3.x;
        } else {
            pp1 = p2; pp2 = p1; u = it3.x; v = it1.x;
        }
        if (v < epsilon || u > 1.f - epsilon) {
            // Segment à l'extérieur du triangle
            result.push_back(tri);
            return;
        }
        sf::Vector2f inter1 = tri.intersection(Segment(lumiere, pp1));
        sf::Vector2f inter2 = tri.intersection(Segment(lumiere, pp2));
        if (-epsilon <= u && v < 1.f + epsilon) {
            // Completement a l'interieur
            result.push_back(Segment(tri.p1, inter1));
            result.push_back(Segment(pp1, pp2));
            result.push_back(Segment(inter2, tri.p2));
            return;
        }
        // On intersecte un seul cote
        if (check(it3.x)) {
            // On intersecte le bout
            result.push_back(Segment(tri.p1, inter1));
            result.push_back(Segment(pp1, si3));
            result.push_back(Segment(si3, tri.p2));
            return;
        } else {
            // On intersecte cote 1
            result.push_back(Segment(si1, pp2));
            result.push_back(Segment(inter2, tri.p2));
            return;
        }
    }
};
